#ifndef ADC_USB_MANAGER_H
#define ADC_USB_MANAGER_H

#include <QObject>
#include <QByteArray>
#include <QString>
#include <QVector>
#include <QList>

#include <libusb-1.0/libusb.h>

#include "adc_proto.h"

class AdcUsbManager : public QObject
{
    Q_OBJECT

public:
    explicit AdcUsbManager(QObject *parent = nullptr);
    ~AdcUsbManager();

    bool isValid() const;

    QList<libusb_device*> enumerateDevices() const;
    bool openDevice(libusb_device *device);
    void closeDevice();
    bool hasDevice() const;

    int32_t readRegister(int reg_index0, int nbytes = 1, int tries = 3);
    void writeRegister(int reg_index0, int32_t reg_value, int nbytes = 1, int tries = 3);

    void handleUsbEvents(int timeout_ms);

signals:
    void packetReceived(const QByteArray &packet);
    void transferTimedOut();
    void usbError(const QString &message);

private:
    struct MemBuf
    {
        bool dev;
        unsigned char *ptr;
        unsigned int length;
    };

    static void LIBUSB_CALL transferCallback(libusb_transfer *transfer);

    void freeTransfers();
    void onTransfer(libusb_transfer *transfer);
    void logLibusbError(const QString &prefix, int code) const;

    libusb_context *ctx;
    libusb_device_handle *current_device;
    QVector<MemBuf> buffers;
    QVector<libusb_transfer*> transfers;
    bool restart_transfers;
    bool valid;
};

#endif // ADC_USB_MANAGER_H
