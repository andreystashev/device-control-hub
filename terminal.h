#ifndef TERMINAL_H
#define TERMINAL_H


class terminal
{
public:
    terminal();
};

#include <QDialog>
#include <QSerialPort>
#include "ui_gravity.h"

QT_BEGIN_NAMESPACE

namespace Ui {
class SettingsDialog;
}

class QIntValidator;

QT_END_NAMESPACE

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    void initialize(Ui::gravity *m_ui);
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
    QIntValidator *m_intValidator = nullptr;


    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

    Settings settings() const;

private slots:

    void showPortInfo(int idx,Ui::gravity *m_ui);
    void apply(Ui::gravity *m_ui);
    void checkCustomBaudRatePolicy(int idx,Ui::gravity *m_ui);
    void checkCustomDevicePathPolicy(int idx,Ui::gravity *m_ui);

private:
    void fillPortsParameters(Ui::gravity *m_ui);
    void fillPortsInfo(Ui::gravity *m_ui);
    void updateSettings(Ui::gravity *m_ui);

private:
    Ui::SettingsDialog *m_ui = nullptr;
    Settings m_currentSettings;
//    QIntValidator *m_intValidator = nullptr;
};



#endif // TERMINAL_H
