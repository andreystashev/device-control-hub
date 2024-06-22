#include <QLineEdit>
#include <QSerialPortInfo>
#include "terminalSettings.h"


static const char blankString[] = QT_TRANSLATE_NOOP("SettingsDialog", "N/A");


void terminalSettings::initialize(Ui::guiUI *m_ui)
{
    m_ui->baudRateBox->setInsertPolicy(QComboBox::NoInsert);
    fillPortsParameters(m_ui);
    fillPortsInfo(m_ui);
    updateSettings(m_ui);
    showPortInfo(0,m_ui);
}


terminalSettings::Settings terminalSettings::settings() const
{
    return m_currentSettings;
}

void terminalSettings::showPortInfo(int idx,Ui::guiUI *m_ui)
{
    if (idx == -1)
        return;

    const QStringList list = m_ui->serialPortInfoListBox->itemData(idx).toStringList();
    m_ui->descriptionLabel->setText(tr("Sign: %1").arg(list.count() > 1 ? list.at(1) : tr(blankString)));
    m_ui->manufacturerLabel->setText(tr("Vendor: %1").arg(list.count() > 2 ? list.at(2) : tr(blankString)));
    m_ui->serialNumberLabel->setText(tr("Serial number: %1").arg(list.count() > 3 ? list.at(3) : tr(blankString)));
    m_ui->locationLabel->setText(tr("Place: %1").arg(list.count() > 4 ? list.at(4) : tr(blankString)));
    m_ui->vidLabel->setText(tr("Vendor ID: %1").arg(list.count() > 5 ? list.at(5) : tr(blankString)));
    m_ui->pidLabel->setText(tr("Product ID: %1").arg(list.count() > 6 ? list.at(6) : tr(blankString)));
}


void terminalSettings::checkCustomBaudRatePolicy(int idx,Ui::guiUI *m_ui)
{
    const bool isCustomBaudRate = !m_ui->baudRateBox->itemData(idx).isValid();
    m_ui->baudRateBox->setEditable(isCustomBaudRate);
    if (isCustomBaudRate) {
        m_ui->baudRateBox->clearEditText();
    }
}

void terminalSettings::checkCustomDevicePathPolicy(int idx,Ui::guiUI *m_ui)
{
    const bool isCustomPath = !m_ui->serialPortInfoListBox->itemData(idx).isValid();
    m_ui->serialPortInfoListBox->setEditable(isCustomPath);
    if (isCustomPath)
        m_ui->serialPortInfoListBox->clearEditText();
}

void terminalSettings::fillPortsParameters(Ui::guiUI *m_ui)
{
    m_ui->baudRateBox->addItem(QStringLiteral("460800"), QSerialPort::BaudRate(460800));
    m_ui->baudRateBox->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    m_ui->baudRateBox->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    m_ui->baudRateBox->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    m_ui->baudRateBox->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
    m_ui->baudRateBox->addItem(tr("Custom"));

    m_ui->dataBitsBox->addItem(QStringLiteral("5"), QSerialPort::Data5);
    m_ui->dataBitsBox->addItem(QStringLiteral("6"), QSerialPort::Data6);
    m_ui->dataBitsBox->addItem(QStringLiteral("7"), QSerialPort::Data7);
    m_ui->dataBitsBox->addItem(QStringLiteral("8"), QSerialPort::Data8);
    m_ui->dataBitsBox->setCurrentIndex(3);

    m_ui->parityBox->addItem(tr("None"), QSerialPort::NoParity);
    m_ui->parityBox->addItem(tr("Even"), QSerialPort::EvenParity);
    m_ui->parityBox->addItem(tr("Odd"), QSerialPort::OddParity);
    m_ui->parityBox->addItem(tr("Mark"), QSerialPort::MarkParity);
    m_ui->parityBox->addItem(tr("Space"), QSerialPort::SpaceParity);

    m_ui->stopBitsBox->addItem(QStringLiteral("1"), QSerialPort::OneStop);
    m_ui->stopBitsBox->addItem(QStringLiteral("2"), QSerialPort::TwoStop);

    m_ui->flowControlBox->addItem(tr("None"), QSerialPort::NoFlowControl);
    m_ui->flowControlBox->addItem(tr("RTS/CTS"), QSerialPort::HardwareControl);
    m_ui->flowControlBox->addItem(tr("XON/XOFF"), QSerialPort::SoftwareControl);
}

void terminalSettings::fillPortsInfo(Ui::guiUI *m_ui)
{
    m_ui->serialPortInfoListBox->clear();
    QString description;
    QString manufacturer;
    QString serialNumber;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        QStringList list;
        description = info.description();
        manufacturer = info.manufacturer();
        serialNumber = info.serialNumber();
        list << info.portName()
             << (!description.isEmpty() ? description : blankString)
             << (!manufacturer.isEmpty() ? manufacturer : blankString)
             << (!serialNumber.isEmpty() ? serialNumber : blankString)
             << info.systemLocation()
             << (info.vendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : blankString)
             << (info.productIdentifier() ? QString::number(info.productIdentifier(), 16) : blankString);

        m_ui->serialPortInfoListBox->addItem(list.first(), list);
    }
    m_ui->serialPortInfoListBox->addItem(tr("Custom"));
}


void terminalSettings::updateSettings(Ui::guiUI *m_ui)
{
    m_currentSettings.name = m_ui->serialPortInfoListBox->currentText();
    if (m_ui->baudRateBox->currentIndex() == 5)
    {
        m_currentSettings.baudRate = m_ui->baudRateBox->currentText().toInt();
    }
    else
    {
        m_currentSettings.baudRate = static_cast<QSerialPort::BaudRate>(m_ui->baudRateBox->itemData(m_ui->baudRateBox->currentIndex()).toInt());
    }
    m_currentSettings.stringBaudRate = QString::number(m_currentSettings.baudRate);
    m_currentSettings.dataBits = static_cast<QSerialPort::DataBits>(m_ui->dataBitsBox->itemData(m_ui->dataBitsBox->currentIndex()).toInt());
    m_currentSettings.stringDataBits = m_ui->dataBitsBox->currentText();
    m_currentSettings.parity = static_cast<QSerialPort::Parity>(m_ui->parityBox->itemData(m_ui->parityBox->currentIndex()).toInt());
    m_currentSettings.stringParity = m_ui->parityBox->currentText();
    m_currentSettings.stopBits = static_cast<QSerialPort::StopBits>(m_ui->stopBitsBox->itemData(m_ui->stopBitsBox->currentIndex()).toInt());
    m_currentSettings.stringStopBits = m_ui->stopBitsBox->currentText();
    m_currentSettings.flowControl = static_cast<QSerialPort::FlowControl>(m_ui->flowControlBox->itemData(m_ui->flowControlBox->currentIndex()).toInt());
    m_currentSettings.stringFlowControl = m_ui->flowControlBox->currentText();
    m_currentSettings.localEchoEnabled = m_ui->localEchoCheckBox->isChecked();
    if(m_ui->actionConnect->isChecked()){
        m_ui->statusBar->setText("Need reconnect");
    }
}
