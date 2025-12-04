#include "adc_usb_manager.h"

#include <QDebug>
#include <QString>

#include <cstdlib>
#include <sys/time.h>

namespace {
constexpr int kTransferCount = 8;
constexpr int kTransferSize = ADC_SAMPLES_COUNT * ADC_PACKET_SIZE;
constexpr int kTransferTimeoutMs = 300;
}

AdcUsbManager::AdcUsbManager(QObject *parent)
    : QObject(parent),
      ctx(nullptr),
      current_device(nullptr),
      restart_transfers(false),
      valid(false)
{
    int res = libusb_init(&ctx);
    if (res != 0)
    {
        qWarning("libusb_init() failed with code %d", res);
        ctx = nullptr;
        return;
    }
    transfers.resize(kTransferCount);
    transfers.fill(nullptr);
    valid = true;
}

AdcUsbManager::~AdcUsbManager()
{
    closeDevice();
    if (ctx)
        libusb_exit(ctx);
}

bool AdcUsbManager::isValid() const
{
    return valid;
}

QList<libusb_device*> AdcUsbManager::enumerateDevices() const
{
    QList<libusb_device*> devices;
    if (!ctx)
        return devices;

    libusb_device **list = nullptr;
    ssize_t count = libusb_get_device_list(ctx, &list);
    if (count < 0)
    {
        qWarning("libusb_get_device_list() failed with code %d", (int)count);
        return devices;
    }

    for (ssize_t i = 0; i < count; ++i)
    {
        libusb_device *device = list[i];
        libusb_device_descriptor desc;
        if (libusb_get_device_descriptor(device, &desc) == 0 &&
            desc.idVendor == ADC_ID_VENDOR &&
            desc.idProduct == ADC_ID_PRODUCT)
        {
            devices.append(device);
        }
        else
        {
            libusb_unref_device(device);
        }
    }
    libusb_free_device_list(list, 0);
    return devices;
}

bool AdcUsbManager::openDevice(libusb_device *device)
{
    if (!ctx)
        return false;

    if (!device)
    {
        closeDevice();
        return false;
    }

    if (current_device && libusb_get_device(current_device) == device)
        return true;

    closeDevice();

    int res = libusb_open(device, &current_device);
    if (res != 0)
    {
        logLibusbError("Error opening device", res);
        current_device = nullptr;
        return false;
    }

#ifndef _WIN32
    if (libusb_kernel_driver_active(current_device, 0))
    {
        res = libusb_detach_kernel_driver(current_device, 0);
        if (res != 0)
        {
            logLibusbError("Error detaching kernel driver", res);
            closeDevice();
            return false;
        }
    }
#endif

    res = libusb_set_configuration(current_device, 1);
    if (res != 0)
        logLibusbError("Error setting configuration", res);

    res = libusb_claim_interface(current_device, 0);
    if (res != 0)
        logLibusbError("Error claiming interface", res);

    buffers.clear();
    buffers.reserve(kTransferCount);
    for (int i = 0; i < kTransferCount; ++i)
    {
        MemBuf buf;
        buf.ptr = libusb_dev_mem_alloc(current_device, kTransferSize);
        if (!(buf.dev = (buf.ptr != nullptr)))
            buf.ptr = static_cast<unsigned char*>(calloc(1, kTransferSize));
        buf.length = kTransferSize;
        buffers.append(buf);
    }

    for (int i = 0; i < kTransferCount; ++i)
    {
        transfers[i] = libusb_alloc_transfer(0);
        if (!transfers[i])
        {
            qWarning("Cannot allocate transfer #%d", i);
            continue;
        }
        libusb_fill_bulk_transfer(transfers[i], current_device, ADC_SAMPLES_EP | 0x80,
                                  buffers[i].ptr, buffers[i].length,
                                  transferCallback,
                                  this, kTransferTimeoutMs);
    }

    restart_transfers = true;
    for (int i = 0; i < kTransferCount; ++i)
    {
        if (!transfers[i])
            continue;
        res = libusb_submit_transfer(transfers[i]);
        if (res != 0)
            qWarning("Cannot submit transfer #%d: error %d", i, res);
    }

    return true;
}

void AdcUsbManager::closeDevice()
{
    if (!current_device)
        return;

    restart_transfers = false;
    for (libusb_transfer *transfer : transfers)
    {
        if (transfer)
            libusb_cancel_transfer(transfer);
    }
    handleUsbEvents(kTransferTimeoutMs);

    freeTransfers();

    libusb_close(current_device);
    current_device = nullptr;
}

bool AdcUsbManager::hasDevice() const
{
    return current_device != nullptr;
}

int32_t AdcUsbManager::readRegister(int reg_index0, int nbytes, int tries)
{
    if (!current_device)
        return 0;
    uint32_t reg_value = 0;
    for (int i = 0; i < nbytes; i++)
    {
        uint8_t value = 0;
        int index = reg_index0 + i;
        for (int ntry = 0; ntry < tries; ntry++)
        {
            int res = libusb_control_transfer(current_device, 0x80 | 0x40, ADC_REQUEST_SETUP, 0, index,
                                              reinterpret_cast<unsigned char*>(&value), 1, kTransferTimeoutMs);
            if (res < 0)
                qWarning("[%d/%d] [index = %d+%d] libusb_control_transfer() => %d",
                         ntry + 1, tries, reg_index0, i, res);
            else
            {
                reg_value |= (static_cast<uint32_t>(value) << (i * 8));
                break;
            }
        }
    }
    return static_cast<int32_t>(reg_value);
}

void AdcUsbManager::writeRegister(int reg_index0, int32_t reg_value, int nbytes, int tries)
{
    if (!current_device)
        return;
    for (int i = 0; i < nbytes; i++)
    {
        int index = reg_index0 + i;
        uint8_t value = (reg_value >> (i * 8)) & 0xff;
        for (int ntry = 0; ntry < tries; ntry++)
        {
            int res = libusb_control_transfer(current_device, 0x40, ADC_REQUEST_SETUP, value, index,
                                              nullptr, 0, kTransferTimeoutMs);
            if (res < 0)
                qWarning("[%d/%d] [index = %d+%d, value = 0x%02x] libusb_control_transfer() => %d",
                         ntry + 1, tries, reg_index0, i, value, res);
            else
                break;
        }
    }
}

void AdcUsbManager::handleUsbEvents(int timeout_ms)
{
    if (!ctx)
        return;
    timeval tv;
    tv.tv_sec = timeout_ms / 1000;
    tv.tv_usec = (timeout_ms % 1000) * 1000;
    int res = libusb_handle_events_timeout(ctx, &tv);
    if (res != 0)
        logLibusbError("libusb_handle_events()", res);
}

void AdcUsbManager::freeTransfers()
{
    for (int i = 0; i < transfers.size(); ++i)
    {
        if (transfers[i])
            libusb_free_transfer(transfers[i]);
        transfers[i] = nullptr;
    }
    for (const MemBuf &buf : buffers)
    {
        if (!buf.ptr)
            continue;
        if (buf.dev)
            libusb_dev_mem_free(current_device, buf.ptr, buf.length);
        else
            free(buf.ptr);
    }
    buffers.clear();
}

void LIBUSB_CALL AdcUsbManager::transferCallback(libusb_transfer *transfer)
{
    if (!transfer || !transfer->user_data)
        return;
    auto *manager = static_cast<AdcUsbManager*>(transfer->user_data);
    manager->onTransfer(transfer);
}

void AdcUsbManager::onTransfer(libusb_transfer *transfer)
{
    if (transfer->status != LIBUSB_TRANSFER_COMPLETED &&
        transfer->status != LIBUSB_TRANSFER_TIMED_OUT)
    {
        qWarning("Transfer %p not completed, status = %d", transfer, transfer->status);
    }
    else
    {
        for (int i = 0; i + static_cast<int>(ADC_PACKET_SIZE) <= transfer->actual_length; i += ADC_PACKET_SIZE)
        {
            QByteArray packet(reinterpret_cast<const char*>(transfer->buffer + i), ADC_PACKET_SIZE);
            emit packetReceived(packet);
        }
        if (transfer->status == LIBUSB_TRANSFER_TIMED_OUT)
            emit transferTimedOut();
    }

    if (!restart_transfers)
        return;

    int res = libusb_submit_transfer(transfer);
    if (res != 0)
        qWarning("Cannot resubmit transfer %p, code = %d", transfer, res);
}

void AdcUsbManager::logLibusbError(const QString &prefix, int code) const
{
    qWarning("%s: code = %d", qPrintable(prefix), code);
}
