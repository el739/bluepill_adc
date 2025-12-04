/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.18
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGroupBox *gbGUICfg;
    QGridLayout *gridLayout_4;
    QLabel *label_14;
    QDoubleSpinBox *dsbVRef;
    QLabel *label_11;
    QSlider *hsTOffset_GUI;
    QLabel *label_12;
    QGroupBox *gbDump;
    QGridLayout *gridLayout_5;
    QLineEdit *leDumpPath;
    QPushButton *pbDoDump;
    QComboBox *cbVScale;
    QLabel *label_15;
    QSlider *hsVOffset_GUI;
    QComboBox *cbTScale;
    QLabel *label_13;
    QSpacerItem *verticalSpacer;
    QLabel *lPlot;
    QGroupBox *gbDeviceCfg;
    QGridLayout *gridLayout_2;
    QGroupBox *gbTrigger;
    QGridLayout *gridLayout_3;
    QSlider *hsTrigLevel;
    QComboBox *cbTrigChannel;
    QLabel *label_8;
    QLabel *label_7;
    QDoubleSpinBox *dsbTrigTMin;
    QDoubleSpinBox *dsbTrigOffset;
    QComboBox *cbTrigger;
    QLabel *label_9;
    QLabel *label_6;
    QLabel *label_10;
    QDoubleSpinBox *dsbTrigTMax;
    QPushButton *pbOnce;
    QGroupBox *gbChannels;
    QLabel *label_3;
    QLabel *label_5;
    QSlider *hsGain;
    QComboBox *cbSamples;
    QPushButton *pbContinuous;
    QSlider *hsOffset;
    QComboBox *cbFrequency;
    QLabel *label_2;
    QLabel *label_4;
    QComboBox *cbNBits;
    QLabel *label;
    QFormLayout *formLayout;
    QMenuBar *menuBar;
    QMenu *menuDevice;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1024, 625);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gbGUICfg = new QGroupBox(centralWidget);
        gbGUICfg->setObjectName(QString::fromUtf8("gbGUICfg"));
        gridLayout_4 = new QGridLayout(gbGUICfg);
        gridLayout_4->setSpacing(3);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        label_14 = new QLabel(gbGUICfg);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_4->addWidget(label_14, 1, 0, 1, 1);

        dsbVRef = new QDoubleSpinBox(gbGUICfg);
        dsbVRef->setObjectName(QString::fromUtf8("dsbVRef"));
        dsbVRef->setSingleStep(0.100000000000000);
        dsbVRef->setValue(3.300000000000000);

        gridLayout_4->addWidget(dsbVRef, 0, 1, 1, 1);

        label_11 = new QLabel(gbGUICfg);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_4->addWidget(label_11, 0, 0, 1, 1);

        hsTOffset_GUI = new QSlider(gbGUICfg);
        hsTOffset_GUI->setObjectName(QString::fromUtf8("hsTOffset_GUI"));
        hsTOffset_GUI->setMaximum(1000);
        hsTOffset_GUI->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(hsTOffset_GUI, 1, 1, 1, 1);

        label_12 = new QLabel(gbGUICfg);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_4->addWidget(label_12, 2, 0, 1, 1);

        gbDump = new QGroupBox(gbGUICfg);
        gbDump->setObjectName(QString::fromUtf8("gbDump"));
        gridLayout_5 = new QGridLayout(gbDump);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        leDumpPath = new QLineEdit(gbDump);
        leDumpPath->setObjectName(QString::fromUtf8("leDumpPath"));

        gridLayout_5->addWidget(leDumpPath, 0, 0, 1, 1);

        pbDoDump = new QPushButton(gbDump);
        pbDoDump->setObjectName(QString::fromUtf8("pbDoDump"));
        pbDoDump->setCheckable(true);

        gridLayout_5->addWidget(pbDoDump, 1, 0, 1, 1);


        gridLayout_4->addWidget(gbDump, 5, 0, 1, 2);

        cbVScale = new QComboBox(gbGUICfg);
        cbVScale->addItem(QString());
        cbVScale->addItem(QString());
        cbVScale->addItem(QString());
        cbVScale->addItem(QString());
        cbVScale->addItem(QString());
        cbVScale->addItem(QString());
        cbVScale->addItem(QString());
        cbVScale->addItem(QString());
        cbVScale->setObjectName(QString::fromUtf8("cbVScale"));

        gridLayout_4->addWidget(cbVScale, 4, 1, 1, 1);

        label_15 = new QLabel(gbGUICfg);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_4->addWidget(label_15, 3, 0, 1, 1);

        hsVOffset_GUI = new QSlider(gbGUICfg);
        hsVOffset_GUI->setObjectName(QString::fromUtf8("hsVOffset_GUI"));
        hsVOffset_GUI->setMaximum(1000);
        hsVOffset_GUI->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(hsVOffset_GUI, 3, 1, 1, 1);

        cbTScale = new QComboBox(gbGUICfg);
        cbTScale->addItem(QString());
        cbTScale->addItem(QString());
        cbTScale->addItem(QString());
        cbTScale->addItem(QString());
        cbTScale->addItem(QString());
        cbTScale->addItem(QString());
        cbTScale->addItem(QString());
        cbTScale->addItem(QString());
        cbTScale->addItem(QString());
        cbTScale->addItem(QString());
        cbTScale->addItem(QString());
        cbTScale->addItem(QString());
        cbTScale->addItem(QString());
        cbTScale->addItem(QString());
        cbTScale->addItem(QString());
        cbTScale->setObjectName(QString::fromUtf8("cbTScale"));

        gridLayout_4->addWidget(cbTScale, 2, 1, 1, 1);

        label_13 = new QLabel(gbGUICfg);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_4->addWidget(label_13, 4, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 6, 0, 1, 2);


        gridLayout->addWidget(gbGUICfg, 1, 2, 1, 1);

        lPlot = new QLabel(centralWidget);
        lPlot->setObjectName(QString::fromUtf8("lPlot"));

        gridLayout->addWidget(lPlot, 1, 1, 1, 1);

        gbDeviceCfg = new QGroupBox(centralWidget);
        gbDeviceCfg->setObjectName(QString::fromUtf8("gbDeviceCfg"));
        gridLayout_2 = new QGridLayout(gbDeviceCfg);
        gridLayout_2->setSpacing(3);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gbTrigger = new QGroupBox(gbDeviceCfg);
        gbTrigger->setObjectName(QString::fromUtf8("gbTrigger"));
        gridLayout_3 = new QGridLayout(gbTrigger);
        gridLayout_3->setSpacing(3);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        hsTrigLevel = new QSlider(gbTrigger);
        hsTrigLevel->setObjectName(QString::fromUtf8("hsTrigLevel"));
        hsTrigLevel->setMaximum(4095);
        hsTrigLevel->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(hsTrigLevel, 2, 1, 1, 1);

        cbTrigChannel = new QComboBox(gbTrigger);
        cbTrigChannel->setObjectName(QString::fromUtf8("cbTrigChannel"));

        gridLayout_3->addWidget(cbTrigChannel, 1, 1, 1, 1);

        label_8 = new QLabel(gbTrigger);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_3->addWidget(label_8, 3, 0, 1, 1);

        label_7 = new QLabel(gbTrigger);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_3->addWidget(label_7, 2, 0, 1, 1);

        dsbTrigTMin = new QDoubleSpinBox(gbTrigger);
        dsbTrigTMin->setObjectName(QString::fromUtf8("dsbTrigTMin"));
        dsbTrigTMin->setDecimals(3);
        dsbTrigTMin->setMinimum(0.000000000000000);
        dsbTrigTMin->setMaximum(9999.000000000000000);
        dsbTrigTMin->setSingleStep(0.050000000000000);

        gridLayout_3->addWidget(dsbTrigTMin, 4, 1, 1, 1);

        dsbTrigOffset = new QDoubleSpinBox(gbTrigger);
        dsbTrigOffset->setObjectName(QString::fromUtf8("dsbTrigOffset"));
        dsbTrigOffset->setDecimals(3);
        dsbTrigOffset->setMinimum(-9999.000000000000000);
        dsbTrigOffset->setMaximum(9999.000000000000000);
        dsbTrigOffset->setSingleStep(0.050000000000000);

        gridLayout_3->addWidget(dsbTrigOffset, 3, 1, 1, 1);

        cbTrigger = new QComboBox(gbTrigger);
        cbTrigger->addItem(QString());
        cbTrigger->addItem(QString());
        cbTrigger->addItem(QString());
        cbTrigger->addItem(QString());
        cbTrigger->addItem(QString());
        cbTrigger->addItem(QString());
        cbTrigger->setObjectName(QString::fromUtf8("cbTrigger"));

        gridLayout_3->addWidget(cbTrigger, 0, 0, 1, 2);

        label_9 = new QLabel(gbTrigger);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_3->addWidget(label_9, 4, 0, 1, 1);

        label_6 = new QLabel(gbTrigger);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_3->addWidget(label_6, 1, 0, 1, 1);

        label_10 = new QLabel(gbTrigger);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_3->addWidget(label_10, 5, 0, 1, 1);

        dsbTrigTMax = new QDoubleSpinBox(gbTrigger);
        dsbTrigTMax->setObjectName(QString::fromUtf8("dsbTrigTMax"));
        dsbTrigTMax->setDecimals(3);
        dsbTrigTMax->setMinimum(0.000000000000000);
        dsbTrigTMax->setMaximum(9999.000000000000000);
        dsbTrigTMax->setSingleStep(0.050000000000000);

        gridLayout_3->addWidget(dsbTrigTMax, 5, 1, 1, 1);


        gridLayout_2->addWidget(gbTrigger, 9, 0, 1, 2);

        pbOnce = new QPushButton(gbDeviceCfg);
        pbOnce->setObjectName(QString::fromUtf8("pbOnce"));

        gridLayout_2->addWidget(pbOnce, 0, 0, 1, 2);

        gbChannels = new QGroupBox(gbDeviceCfg);
        gbChannels->setObjectName(QString::fromUtf8("gbChannels"));

        gridLayout_2->addWidget(gbChannels, 3, 0, 1, 2);

        label_3 = new QLabel(gbDeviceCfg);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 6, 0, 1, 1);

        label_5 = new QLabel(gbDeviceCfg);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 8, 0, 1, 1);

        hsGain = new QSlider(gbDeviceCfg);
        hsGain->setObjectName(QString::fromUtf8("hsGain"));
        hsGain->setMaximum(11);
        hsGain->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(hsGain, 8, 1, 1, 1);

        cbSamples = new QComboBox(gbDeviceCfg);
        cbSamples->addItem(QString());
        cbSamples->addItem(QString());
        cbSamples->addItem(QString());
        cbSamples->addItem(QString());
        cbSamples->addItem(QString());
        cbSamples->addItem(QString());
        cbSamples->addItem(QString());
        cbSamples->addItem(QString());
        cbSamples->addItem(QString());
        cbSamples->addItem(QString());
        cbSamples->addItem(QString());
        cbSamples->setObjectName(QString::fromUtf8("cbSamples"));

        gridLayout_2->addWidget(cbSamples, 6, 1, 1, 1);

        pbContinuous = new QPushButton(gbDeviceCfg);
        pbContinuous->setObjectName(QString::fromUtf8("pbContinuous"));
        pbContinuous->setCheckable(true);

        gridLayout_2->addWidget(pbContinuous, 1, 0, 1, 2);

        hsOffset = new QSlider(gbDeviceCfg);
        hsOffset->setObjectName(QString::fromUtf8("hsOffset"));
        hsOffset->setMaximum(4095);
        hsOffset->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(hsOffset, 7, 1, 1, 1);

        cbFrequency = new QComboBox(gbDeviceCfg);
        cbFrequency->addItem(QString());
        cbFrequency->addItem(QString());
        cbFrequency->addItem(QString());
        cbFrequency->addItem(QString());
        cbFrequency->addItem(QString());
        cbFrequency->addItem(QString());
        cbFrequency->addItem(QString());
        cbFrequency->addItem(QString());
        cbFrequency->addItem(QString());
        cbFrequency->addItem(QString());
        cbFrequency->addItem(QString());
        cbFrequency->setObjectName(QString::fromUtf8("cbFrequency"));

        gridLayout_2->addWidget(cbFrequency, 5, 1, 1, 1);

        label_2 = new QLabel(gbDeviceCfg);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 5, 0, 1, 1);

        label_4 = new QLabel(gbDeviceCfg);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 7, 0, 1, 1);

        cbNBits = new QComboBox(gbDeviceCfg);
        cbNBits->addItem(QString());
        cbNBits->addItem(QString());
        cbNBits->addItem(QString());
        cbNBits->addItem(QString());
        cbNBits->setObjectName(QString::fromUtf8("cbNBits"));

        gridLayout_2->addWidget(cbNBits, 4, 1, 1, 1);

        label = new QLabel(gbDeviceCfg);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 4, 0, 1, 1);


        gridLayout->addWidget(gbDeviceCfg, 1, 0, 1, 1);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));

        gridLayout->addLayout(formLayout, 0, 1, 1, 1);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 3);
        gridLayout->setColumnStretch(2, 1);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 30));
        menuDevice = new QMenu(menuBar);
        menuDevice->setObjectName(QString::fromUtf8("menuDevice"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        statusBar->setLayoutDirection(Qt::RightToLeft);
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuDevice->menuAction());

        retranslateUi(MainWindow);

        cbTScale->setCurrentIndex(3);
        cbSamples->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Multichannel Analog-to-Digital USB-converter", nullptr));
        gbGUICfg->setTitle(QCoreApplication::translate("MainWindow", "GUI config", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "T offset", nullptr));
        dsbVRef->setSuffix(QCoreApplication::translate("MainWindow", "V", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Vref", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "T scale", nullptr));
        gbDump->setTitle(QCoreApplication::translate("MainWindow", "Dump data", nullptr));
        leDumpPath->setText(QCoreApplication::translate("MainWindow", "./adc.log", nullptr));
        pbDoDump->setText(QCoreApplication::translate("MainWindow", "Dump", nullptr));
        cbVScale->setItemText(0, QCoreApplication::translate("MainWindow", "4 V", nullptr));
        cbVScale->setItemText(1, QCoreApplication::translate("MainWindow", "2 V", nullptr));
        cbVScale->setItemText(2, QCoreApplication::translate("MainWindow", "1 V", nullptr));
        cbVScale->setItemText(3, QCoreApplication::translate("MainWindow", "400 mV", nullptr));
        cbVScale->setItemText(4, QCoreApplication::translate("MainWindow", "200 mV", nullptr));
        cbVScale->setItemText(5, QCoreApplication::translate("MainWindow", "100 mV", nullptr));
        cbVScale->setItemText(6, QCoreApplication::translate("MainWindow", "40 mV", nullptr));
        cbVScale->setItemText(7, QCoreApplication::translate("MainWindow", "20 mV", nullptr));

        label_15->setText(QCoreApplication::translate("MainWindow", "V offset", nullptr));
        cbTScale->setItemText(0, QCoreApplication::translate("MainWindow", "100 us", nullptr));
        cbTScale->setItemText(1, QCoreApplication::translate("MainWindow", "200 us", nullptr));
        cbTScale->setItemText(2, QCoreApplication::translate("MainWindow", "500 us", nullptr));
        cbTScale->setItemText(3, QCoreApplication::translate("MainWindow", "1 ms", nullptr));
        cbTScale->setItemText(4, QCoreApplication::translate("MainWindow", "2 ms", nullptr));
        cbTScale->setItemText(5, QCoreApplication::translate("MainWindow", "5 ms", nullptr));
        cbTScale->setItemText(6, QCoreApplication::translate("MainWindow", "10 ms", nullptr));
        cbTScale->setItemText(7, QCoreApplication::translate("MainWindow", "20 ms", nullptr));
        cbTScale->setItemText(8, QCoreApplication::translate("MainWindow", "50 ms", nullptr));
        cbTScale->setItemText(9, QCoreApplication::translate("MainWindow", "100 ms", nullptr));
        cbTScale->setItemText(10, QCoreApplication::translate("MainWindow", "200 ms", nullptr));
        cbTScale->setItemText(11, QCoreApplication::translate("MainWindow", "500 ms", nullptr));
        cbTScale->setItemText(12, QCoreApplication::translate("MainWindow", "1 sec", nullptr));
        cbTScale->setItemText(13, QCoreApplication::translate("MainWindow", "2 sec", nullptr));
        cbTScale->setItemText(14, QCoreApplication::translate("MainWindow", "5 sec", nullptr));

        label_13->setText(QCoreApplication::translate("MainWindow", "V scale", nullptr));
        lPlot->setText(QString());
        gbDeviceCfg->setTitle(QCoreApplication::translate("MainWindow", "Device config", nullptr));
        gbTrigger->setTitle(QCoreApplication::translate("MainWindow", "Trigger", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "T offset", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "level", nullptr));
        dsbTrigTMin->setSuffix(QCoreApplication::translate("MainWindow", "ms", nullptr));
        dsbTrigOffset->setSuffix(QCoreApplication::translate("MainWindow", "ms", nullptr));
        cbTrigger->setItemText(0, QCoreApplication::translate("MainWindow", "NONE", nullptr));
        cbTrigger->setItemText(1, QCoreApplication::translate("MainWindow", "RISING", nullptr));
        cbTrigger->setItemText(2, QCoreApplication::translate("MainWindow", "FALLING", nullptr));
        cbTrigger->setItemText(3, QCoreApplication::translate("MainWindow", "THRESHOLD", nullptr));
        cbTrigger->setItemText(4, QCoreApplication::translate("MainWindow", "STROBE LO", nullptr));
        cbTrigger->setItemText(5, QCoreApplication::translate("MainWindow", "STROBE HI", nullptr));

        label_9->setText(QCoreApplication::translate("MainWindow", "Strobe min", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "channel", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Strobe max", nullptr));
        dsbTrigTMax->setSuffix(QCoreApplication::translate("MainWindow", "ms", nullptr));
        pbOnce->setText(QCoreApplication::translate("MainWindow", "Start once", nullptr));
        gbChannels->setTitle(QCoreApplication::translate("MainWindow", "Channels", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "samples", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "gain", nullptr));
        cbSamples->setItemText(0, QCoreApplication::translate("MainWindow", "1024", nullptr));
        cbSamples->setItemText(1, QCoreApplication::translate("MainWindow", "2048", nullptr));
        cbSamples->setItemText(2, QCoreApplication::translate("MainWindow", "4096", nullptr));
        cbSamples->setItemText(3, QCoreApplication::translate("MainWindow", "8192", nullptr));
        cbSamples->setItemText(4, QCoreApplication::translate("MainWindow", "16384", nullptr));
        cbSamples->setItemText(5, QCoreApplication::translate("MainWindow", "32768", nullptr));
        cbSamples->setItemText(6, QCoreApplication::translate("MainWindow", "65536", nullptr));
        cbSamples->setItemText(7, QCoreApplication::translate("MainWindow", "131072", nullptr));
        cbSamples->setItemText(8, QCoreApplication::translate("MainWindow", "262144", nullptr));
        cbSamples->setItemText(9, QCoreApplication::translate("MainWindow", "524288", nullptr));
        cbSamples->setItemText(10, QCoreApplication::translate("MainWindow", "1048576", nullptr));

        pbContinuous->setText(QCoreApplication::translate("MainWindow", "Continuous", nullptr));
        cbFrequency->setItemText(0, QCoreApplication::translate("MainWindow", "STOPPED", nullptr));
        cbFrequency->setItemText(1, QCoreApplication::translate("MainWindow", "MAX", nullptr));
        cbFrequency->setItemText(2, QCoreApplication::translate("MainWindow", "500 kHz", nullptr));
        cbFrequency->setItemText(3, QCoreApplication::translate("MainWindow", "200 kHz", nullptr));
        cbFrequency->setItemText(4, QCoreApplication::translate("MainWindow", "100 kHz", nullptr));
        cbFrequency->setItemText(5, QCoreApplication::translate("MainWindow", "50 kHz", nullptr));
        cbFrequency->setItemText(6, QCoreApplication::translate("MainWindow", "20 kHz", nullptr));
        cbFrequency->setItemText(7, QCoreApplication::translate("MainWindow", "10 kHz", nullptr));
        cbFrequency->setItemText(8, QCoreApplication::translate("MainWindow", "5 kHz", nullptr));
        cbFrequency->setItemText(9, QCoreApplication::translate("MainWindow", "2 kHz", nullptr));
        cbFrequency->setItemText(10, QCoreApplication::translate("MainWindow", "1 kHz", nullptr));

        label_2->setText(QCoreApplication::translate("MainWindow", "freq", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "offset", nullptr));
        cbNBits->setItemText(0, QCoreApplication::translate("MainWindow", "DIGITAL (2)", nullptr));
        cbNBits->setItemText(1, QCoreApplication::translate("MainWindow", "LO (4)", nullptr));
        cbNBits->setItemText(2, QCoreApplication::translate("MainWindow", "MID (8)", nullptr));
        cbNBits->setItemText(3, QCoreApplication::translate("MainWindow", "HI (12)", nullptr));

        label->setText(QCoreApplication::translate("MainWindow", "bits", nullptr));
        menuDevice->setTitle(QCoreApplication::translate("MainWindow", "Device", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
