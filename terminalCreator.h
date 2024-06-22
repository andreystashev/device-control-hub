#ifndef WINDOWTERMINAL_H
#define WINDOWTERMINAL_H
#include <QSerialPort>
#include "ui_guicreator.h"
#include "terminalSettings.h"
#include "networkcreator.h"


class QLabel;
class Console;
class terminalSettings;


class terminalCreator: public QObject
{
    Q_OBJECT

public:
    explicit terminalCreator() {};

public slots:
    void openSerialPort(Ui::guiUI *m_ui);
    void closeSerialPort(Ui::guiUI *m_ui);
    void readData();
    void changeTerminalSettingsHere(Ui::guiUI *m_ui);
    void handleError(QSerialPort::SerialPortError error);
    void showTerminalPortInfoHere(int idx,Ui::guiUI *m_ui);
    void checkTerminalCustomBaudRatePolicyHere(int idx,Ui::guiUI *m_ui);
    void checkTerminalCustomDevicePathPolicyHere(int idx,Ui::guiUI *m_ui);
    void sendFile(int);
    void sendEmptyFile(int);
    void sendStatus();
    void readInfo(QByteArray fileData);
    void nothing();
    void allFilesIsSentSlot();

signals:
    void closeSerialPortSignal();
    void TarrayNewByteSend(QByteArray*,uint16_t);


private:
    void showStatusMessage(const QString &message,Ui::guiUI *m_ui);

    Ui::guiUI *t_ui;
    QTimer *timer;
    Console *m_console = nullptr;
    terminalSettings *m_settings = nullptr;
    QSerialPort *m_serial = nullptr;
    QString terminalFilePath = "files/";
};

#endif // WINDOWTERMINAL_H
