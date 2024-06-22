#ifndef SETTINGSTERMINAL_H
#define SETTINGSTERMINAL_H
#include <QSerialPort>
#include "ui_guicreator.h"


class terminalSettings:public QObject

{
    Q_OBJECT
public:
    Ui::guiUI *ui;
    explicit terminalSettings(){};
    void updateSettings(Ui::guiUI *m_ui);

    struct Settings {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
        bool localEchoEnabled;
    };
    void initialize(Ui::guiUI *m_ui);

    Settings settings() const;

public slots:
    void showPortInfo(int idx,Ui::guiUI *m_ui);
    void checkCustomBaudRatePolicy(int idx,Ui::guiUI *m_ui);
    void checkCustomDevicePathPolicy(int idx,Ui::guiUI *m_ui);

private:
    void fillPortsParameters(Ui::guiUI *m_ui);
    void fillPortsInfo(Ui::guiUI *m_ui);

private:

    Settings m_currentSettings;
};

#endif // SETTINGSTERMINAL_H










