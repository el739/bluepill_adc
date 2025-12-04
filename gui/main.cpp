#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

#include "adc_usb_manager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AdcUsbManager usbManager;
    if (!usbManager.isValid())
    {
        qDebug("Can't start app: libusb_init() failed");
        return 1;
    }

    MainWindow w(&usbManager);
    w.show();

    return a.exec();
}
