#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCheckBox>
#include <QDebug>
#include <QGridLayout>
#include <QPixmap>
#include <QStringList>

static QList<int> bits(uint16_t v)
{
    QList<int> ret;
    for (int i = 0; i < 16; i++)
        if (v & (1 << i))
            ret.push_back(i);
    return ret;
}

double MainWindow::samplePeriod(int frequency_code)
{
    int freq = 0;
    switch (frequency_code)
    {
    default:
    case ADC_FREQUENCY_OFF:
        return 0.0;
    case ADC_FREQUENCY_MAX:
        freq = 857143;
        break;
    case ADC_FREQUENCY_500KHZ:
        freq = 500000;
        break;
    case ADC_FREQUENCY_200KHZ:
        freq = 200000;
        break;
    case ADC_FREQUENCY_100KHZ:
        freq = 100000;
        break;
    case ADC_FREQUENCY_50KHZ:
        freq = 50000;
        break;
    case ADC_FREQUENCY_20KHZ:
        freq = 20000;
        break;
    case ADC_FREQUENCY_10KHZ:
        freq = 10000;
        break;
    case ADC_FREQUENCY_5KHZ:
        freq = 5000;
        break;
    case ADC_FREQUENCY_2KHZ:
        freq = 2000;
        break;
    case ADC_FREQUENCY_1KHZ:
        freq = 1000;
        break;
    }
    double ret = 1.0 / (double)freq;
    if (channels_in_use > 1) // two ADCs in Dual mode
        ret *= 0.5;
    else if (channels_in_use == 1 && frequency_code == ADC_FREQUENCY_MAX) // two ADCs in Fast interleave mode
        ret *= 0.5;
    ret *= (double)channels_in_use;
    return ret;
}

void MainWindow::updateStatistics(int bytes, int packets, int samples, int periods, int lost)
{
    bytes_received += bytes;
    packets_received += packets;
    samples_received += samples;
    periods_received += periods;
    packets_lost += lost;

    if (statistic_timer.elapsed() > 2000)
    {
        double dt = (double)statistic_timer.elapsed() * 0.001;
        double kbps = (double)bytes_received * 8.0 / 1024.0 / dt;
        double ksmps = (double)periods_received / 1000.0 / dt;
        double loss = 100.0 * (double)packets_lost / (double)(packets_lost + packets_received);

        ui->statusBar->showMessage(
                    tr("%1 kBit/s; %2 kS/s; loss %3%")
                    .arg(kbps, 0, 'f', 1)
                    .arg(ksmps, 0, 'f', 2)
                    .arg(loss, 0, 'f', 1));

        resetStatistics();
    }
}

void MainWindow::redrawSamples(bool force)
{
    if (!force && (!redraw_needed || redraw_timer.elapsed() < 40))
        return;
    redraw_timer.start();

    if (ts_data.isEmpty())
        return;

    PlotOptions options;
    QStringList tscale_parts = ui->cbTScale->currentText().split(' ');
    double tscale = tscale_parts[0].toDouble();
    if (tscale_parts.size() > 1 && tscale_parts[1] == "us")
        tscale *= 1e-6;
    else if (tscale_parts.size() > 1 && tscale_parts[1] == "ms")
        tscale *= 1e-3;

    QStringList vscale_parts = ui->cbVScale->currentText().split(' ');
    double vscale = vscale_parts[0].toDouble();
    if (vscale_parts.size() > 1 && vscale_parts[1] == "uV")
        vscale *= 1e-6;
    else if (vscale_parts.size() > 1 && vscale_parts[1] == "mV")
        vscale *= 1e-3;

    options.timeScaleSeconds = tscale;
    options.timeOffsetRatio = (double)ui->hsTOffset_GUI->value() / 1000.0;
    options.voltageScaleVolts = vscale;
    options.voltageOffsetRatio = (double)ui->hsVOffset_GUI->value() / 1000.0;
    options.referenceVoltage = ui->dsbVRef->value();
    options.triggerLevelVolts = (double)ui->hsTrigLevel->value() / (double)ADC_MAX_LEVEL * options.referenceVoltage;
    options.triggerEnabled = (ui->cbTrigger->currentIndex() > 0);
    options.canvasSize = ui->lPlot->size();
    options.channelColors = QVector<QColor>();
    options.channelColors.reserve(ADC_TOTAL_CHANNELS);
    for (int i = 0; i < ADC_TOTAL_CHANNELS; ++i)
        options.channelColors.append(channels_color[i]);

    QPixmap pixmap = plot_renderer.render(ts_data, vs_data, options);
    if (!pixmap.isNull())
    {
        ui->lPlot->setPixmap(pixmap);
        ui->lPlot->repaint();
    }

    redraw_needed = false;
}

void MainWindow::resetStatistics()
{
    statistic_timer.start();
    bytes_received = packets_received = samples_received = periods_received = 0;
    packets_lost = 0;
}

void MainWindow::updateData(int packet_num, int freq_code, const QList<int> &channels, const QList<uint16_t> &samples)
{
    double dt = samplePeriod(freq_code);
    double packet_period = dt / channels.size() * samples.size();
    double t0 = (double)packet_num * packet_period;

    if (ts_data.size() > 0 && t0 < ts_data.last())
    {
        ts_data.clear();
        vs_data.clear();
        redraw_needed = true;
    }

    if (!ui->pbDoDump->isChecked() && dump.isOpen())
        dump.close();
    if (ui->pbDoDump->isChecked() && !(dump.fileName() == ui->leDumpPath->text() && dump.isOpen()))
    {
        if (dump.isOpen())
            dump.close();
        dump.setFileName(ui->leDumpPath->text());
        dump.open(QIODevice::WriteOnly);

        dump.write("T[ms]");
        for (int ch = 0; ch < channels.size(); ch++)
        {
            int ch_num = channels[ch];
            if (channels_box[ch_num]->isChecked())
                dump.write(QString("\tCH.%1").arg(ch_num + 1).toLatin1());
        }
        dump.write("\n");
    }

    for (int i = 0; i < samples.size() / channels.size(); i++)
    {
        double t = t0 + i * dt;
        ts_data.append(t);
        if (dump.isOpen())
            dump.write(QString("%1").arg(t * 1e3, 0, 'f', 3).toLatin1());
        for (int ch = 0; ch < channels.size(); ch++)
        {
            int ch_num = channels[ch];
            if (!channels_box[ch_num]->isChecked())
                continue;
            double v = (double)samples[i * channels.size() + ch] / (double)ADC_MAX_LEVEL * ui->dsbVRef->value();
            if (!vs_data.contains(ch_num))
                vs_data[ch_num] = QList<double>();
            vs_data[ch_num].append(v);
            if (dump.isOpen())
                dump.write(QString("\t%1").arg(v * 1e3, 0, 'f', 3).toLatin1());
        }
        if (dump.isOpen())
            dump.write("\n");
    }
    redraw_needed = (samples.size() > 0);
}

void MainWindow::parseADCPacket(const QByteArray &packet)
{
    if (packet.size() < (int)ADC_PACKET_SIZE)
        return;

    const unsigned char *raw_packet = reinterpret_cast<const unsigned char*>(packet.constData());
    const ADCPacketHeader * header = reinterpret_cast<const ADCPacketHeader*>(raw_packet);
    const uint8_t * data = raw_packet + sizeof(ADCPacketHeader);
    int length = ADC_PACKET_SIZE - sizeof(ADCPacketHeader);

    int lost = 0;

    int seq_n = (header->sequence & 0x7f);
    if (last_seq < 0 || (header->sequence & 0x80))
    {
        if (last_seq >= 0)
            redrawSamples();
        seq_t0 = seq_n;
        last_seq = seq_n;
    }
    else
    {
        uint8_t next_seq = (uint8_t)(last_seq + 1);
        lost = (int)((seq_n - next_seq + 0x80) & 0x7f);
        last_seq += lost + 1;
    }

    QList<int> channels = bits(header->channels);
    int nbits = (header->mode & ADC_MODE_BITS);
    int freq_code = (header->mode & ADC_MODE_FREQUENCY) >> 4;

    if (channels.size() == 0)
        return;

    QList<uint16_t> samples;
    int i;
    switch (nbits)
    {
    default:
        return;
    case ADC_BITS_DIGITAL:
        for (i = 0; i < length; i++)
        {
            samples.push_back((uint16_t)(data[i] & 0xc0) <<  4);
            samples.push_back((uint16_t)(data[i] & 0x30) <<  6);
            samples.push_back((uint16_t)(data[i] & 0x0c) <<  8);
            samples.push_back((uint16_t)(data[i] & 0x03) << 10);
        }
        break;
    case ADC_BITS_LO:
        for (i = 0; i < length; i++)
        {
            samples.push_back((uint16_t)(data[i] & 0xf0) << 4);
            samples.push_back((uint16_t)(data[i] & 0x0f) << 8);
        }
        break;
    case ADC_BITS_MID:
        for (i = 0; i < length; i++)
            samples.push_back((uint16_t)data[i] << 4);
        break;
    case ADC_BITS_HI:
        for (i = 0; i < length; i += 3)
        {
            samples.push_back(((uint16_t)data[i+0] << 4) | (((uint16_t)data[i+1] >> 4) & 0x0f));
            samples.push_back(((uint16_t)data[i+2] << 4) | (((uint16_t)data[i+1] >> 0) & 0x0f));
        }
        break;
    }

    updateData(last_seq - seq_t0, freq_code, channels, samples);
    updateStatistics(ADC_PACKET_SIZE, 1, samples.size(), samples.size() / channels.size(), lost);
}

void MainWindow::onAdcPacket(const QByteArray &packet)
{
    parseADCPacket(packet);
}

int32_t MainWindow::readRegister(int reg_index0, int nbytes, int tries)
{
    if (!usb_manager)
        return 0;
    return usb_manager->readRegister(reg_index0, nbytes, tries);
}

void MainWindow::writeRegister(int reg_index0, int32_t reg_value, int nbytes, int tries)
{
    if (!usb_manager)
        return;
    usb_manager->writeRegister(reg_index0, reg_value, nbytes, tries);
}

void MainWindow::readConfig()
{
    ui->pbContinuous->setChecked(readRegister(ADC_INDEX_CMD) == ADC_CMD_CONTINUOUS);

    int32_t channels = readRegister(ADC_INDEX_CHANNELS, 2);
    int32_t use_channels = readRegister(ADC_INDEX_USE_CHANNELS, 2);
    channels_in_use = 0;
    for (int i = 0; i < channels_box.size(); i++)
    {
        channels_box[i]->setChecked(channels & (1 << i));
        if (use_channels & (1 << i))
            channels_in_use++;
    }

    switch (readRegister(ADC_INDEX_BITS))
    {
    case ADC_BITS_DIGITAL:
        ui->cbNBits->setCurrentIndex(0);
        break;
    case ADC_BITS_LO:
        ui->cbNBits->setCurrentIndex(1);
        break;
    case ADC_BITS_MID:
        ui->cbNBits->setCurrentIndex(2);
        break;
    case ADC_BITS_HI:
        ui->cbNBits->setCurrentIndex(3);
        break;
    }

    ui->cbFrequency->setCurrentIndex(readRegister(ADC_INDEX_FREQUENCY));
    ui->cbSamples->setCurrentIndex(readRegister(ADC_INDEX_SAMPLES));
    ui->hsOffset->setValue(readRegister(ADC_INDEX_OFFSET, 2));
    ui->hsGain->setValue(readRegister(ADC_INDEX_GAIN));
    ui->cbTrigger->setCurrentIndex(readRegister(ADC_INDEX_TRIGGER));
    ui->cbTrigChannel->setCurrentIndex(readRegister(ADC_INDEX_TRIG_CHANNEL));
    ui->hsTrigLevel->setValue(readRegister(ADC_INDEX_TRIG_LEVEL, 2));

    double dt = samplePeriod(ui->cbFrequency->currentIndex()) * 1000.0;
    ui->dsbTrigOffset->setValue(dt * (double)readRegister(ADC_INDEX_TRIG_OFFSET, 4));
    ui->dsbTrigTMin->setValue(dt * (double)readRegister(ADC_INDEX_TRIG_T_MIN, 4));
    ui->dsbTrigTMax->setValue(dt * (double)readRegister(ADC_INDEX_TRIG_T_MAX, 4));
}

MainWindow::MainWindow(AdcUsbManager *manager, QWidget *parent) :
    QMainWindow(parent),
    usb_manager(manager),
    last_seq(-1),
    seq_t0(0),
    bytes_received(0),
    packets_received(0),
    samples_received(0),
    periods_received(0),
    packets_lost(0),
    channels_in_use(0),
    redraw_needed(true),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&event_timer, SIGNAL(timeout()), this, SLOT(handleUsbEvents()));
    connect(ui->menuDevice, SIGNAL(triggered(QAction*)), this, SLOT(deviceSelected(QAction*)));

    if (usb_manager)
    {
        connect(usb_manager, &AdcUsbManager::packetReceived,
                this, &MainWindow::onAdcPacket);
        connect(usb_manager, &AdcUsbManager::transferTimedOut,
                this, [this]() { redrawSamples(); });
        connect(usb_manager, &AdcUsbManager::usbError,
                this, &MainWindow::onUsbError);
    }

    QGridLayout * grid = new QGridLayout();
    for (int nch = 0; nch < ADC_TOTAL_CHANNELS; nch++)
    {
        QColor color = channels_color[nch];
        QString name = tr("CH.%1").arg(nch+1);
        ui->cbTrigChannel->addItem(name);
        QCheckBox * box = new QCheckBox(name);
        box->setStyleSheet(QString("background-color: rgb(%1, %2, %3);")
                           .arg(color.red())
                           .arg(color.green())
                           .arg(color.blue()));
        grid->addWidget(box, nch / 3, nch % 3);
        connect(box, SIGNAL(clicked(bool)), this, SLOT(updateChannelsSelection()));
        channels_box.push_back(box);
    }
    grid->setSpacing(0);
    ui->gbChannels->setLayout(grid);

    event_timer.setInterval(20);
    event_timer.start();

    redraw_timer.start();

    refreshDevicesList();
}

MainWindow::~MainWindow()
{
    if (usb_manager)
        usb_manager->closeDevice();
    delete ui;
}

void MainWindow::handleUsbEvents(int timeout_ms)
{
    if (!usb_manager)
        return;
    usb_manager->handleUsbEvents(timeout_ms);
}

void MainWindow::clearDevicesList()
{
    foreach (QAction * action, ui->menuDevice->actions())
    {
        libusb_device * dev = (libusb_device*)action->data().toULongLong();
        if (dev)
            libusb_unref_device(dev);
    }
    ui->menuDevice->clear();
    QAction *refreshAction = ui->menuDevice->addAction(tr("Refresh list"));
    refreshAction->setData((qulonglong)0);
    ui->menuDevice->addSeparator();
}

void MainWindow::refreshDevicesList()
{
    clearDevicesList();

    if (!usb_manager)
        return;

    int adcs_added = 0;
    QList<libusb_device*> devices = usb_manager->enumerateDevices();
    for (libusb_device *device : devices)
    {
        QString name = tr("bus = %1, port = %2, address = %3")
                .arg(libusb_get_bus_number(device))
                .arg(libusb_get_port_number(device))
                .arg(libusb_get_device_address(device));
        QAction *act = ui->menuDevice->addAction(name);
        act->setData((qulonglong)device);
        adcs_added++;
    }

    if (adcs_added == 1)
        deviceSelected(ui->menuDevice->actions().last());
    else if (adcs_added == 0)
        ui->statusBar->showMessage(tr("disconnected"));
}

void MainWindow::deviceSelected(QAction *action)
{
    if (!usb_manager)
        return;

    libusb_device * dev = (libusb_device*)action->data().toULongLong();
    if (!dev)
        refreshDevicesList();
    else
    {
        if (usb_manager->openDevice(dev))
        {
            resetStatistics();
            readConfig();
            ui->statusBar->showMessage(tr("connected"));
        }
        else
            ui->statusBar->showMessage(tr("connection failed"));
    }
}

void MainWindow::onUsbError(const QString &message)
{
    ui->statusBar->showMessage(message);
}

void MainWindow::updateChannelsSelection()
{
    uint32_t channels = 0;
    for (int i = 0; i < channels_box.size(); i++)
        if (channels_box[i]->isChecked())
            channels |= (1 << i);
    writeRegister(ADC_INDEX_CHANNELS, channels, 2);
    readConfig();
}

void MainWindow::on_cbNBits_currentIndexChanged(int index)
{
    switch (index)
    {
    case 0:
        writeRegister(ADC_INDEX_BITS, ADC_BITS_DIGITAL);
        break;
    case 1:
        writeRegister(ADC_INDEX_BITS, ADC_BITS_LO);
        break;
    case 2:
        writeRegister(ADC_INDEX_BITS, ADC_BITS_MID);
        break;
    case 3:
        writeRegister(ADC_INDEX_BITS, ADC_BITS_HI);
        break;
    default:
        break;
    }
}

void MainWindow::on_cbFrequency_currentIndexChanged(int index)
{
    writeRegister(ADC_INDEX_FREQUENCY, index);
    readConfig();
}

void MainWindow::on_cbSamples_currentIndexChanged(int index)
{
    writeRegister(ADC_INDEX_SAMPLES, index);
}

void MainWindow::on_hsOffset_valueChanged(int value)
{
    writeRegister(ADC_INDEX_OFFSET, value, 2);
}

void MainWindow::on_hsGain_valueChanged(int value)
{
    writeRegister(ADC_INDEX_GAIN, value);
}

void MainWindow::on_cbTrigger_currentIndexChanged(int index)
{
    writeRegister(ADC_INDEX_TRIGGER, index);
}

void MainWindow::on_cbTrigChannel_currentIndexChanged(int index)
{
    writeRegister(ADC_INDEX_TRIG_CHANNEL, index);
}

void MainWindow::on_hsTrigLevel_valueChanged(int value)
{
    writeRegister(ADC_INDEX_TRIG_LEVEL, value, 2);
    redraw_needed = true;
}

void MainWindow::on_dsbTrigOffset_valueChanged(double arg1)
{
    double dt = samplePeriod(ui->cbFrequency->currentIndex());
    if (dt == 0)
        return;
    int offset = int(arg1 * 0.001 / dt);
    writeRegister(ADC_INDEX_TRIG_OFFSET, offset, 4);
}

void MainWindow::on_dsbTrigTMin_valueChanged(double arg1)
{
    double dt = samplePeriod(ui->cbFrequency->currentIndex());
    if (dt == 0)
        return;
    int t_min = int(arg1 * 0.001 / dt);
    writeRegister(ADC_INDEX_TRIG_T_MIN, t_min, 4);
}

void MainWindow::on_dsbTrigTMax_valueChanged(double arg1)
{
    double dt = samplePeriod(ui->cbFrequency->currentIndex());
    if (dt == 0)
        return;
    int t_max = int(arg1 * 0.001 / dt);
    writeRegister(ADC_INDEX_TRIG_T_MAX, t_max, 4);
}

void MainWindow::on_cbTScale_currentIndexChanged(int)
{
    redrawSamples(true);
}

void MainWindow::on_hsTOffset_GUI_valueChanged(int)
{
    redrawSamples(true);
}

void MainWindow::on_hsVOffset_GUI_valueChanged(int)
{
    redrawSamples(true);
}

void MainWindow::on_cbVScale_currentIndexChanged(int)
{
    redrawSamples(true);
}

void MainWindow::on_pbOnce_clicked()
{
    ui->pbContinuous->setChecked(false);
    writeRegister(ADC_INDEX_CMD, ADC_CMD_ONCE);

}

void MainWindow::on_pbContinuous_clicked()
{
    writeRegister(ADC_INDEX_CMD,
                      ui->pbContinuous->isChecked() ?
                          ADC_CMD_CONTINUOUS :
                          ADC_CMD_STOP);
}
