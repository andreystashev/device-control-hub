#include <QLabel>
#include <QMessageBox>
#include <QXmlStreamReader>
#include "messages.h"
#include "terminalCreator.h"
#include "terminalConsole.h"


uint16_t CRC(const void *p, uint8_t len)
{
    const uint8_t *ptr = (const uint8_t *) p;
    uint8_t mas[len];
    long unsigned int j=0,k=0;
    for(j=1;j<len;j++)
        mas[k++] = j;
    uint8_t crc = 0xFF;
    uint8_t crcLo = 0xFF;
    do
    {
        uint8_t i = crc ^ *ptr++;
        crc = crcLo ^ (uint8_t) (mas[i]);
        crcLo = (uint8_t) (mas[i]);
    } while (--len);
    return ((crc << 8) | crcLo);
}


static const uint8_t auchCRCHi[256] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E
};


static const uint8_t auchCRCLo[256] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E,
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E
};


uint16_t CRC256(const void *p, uint len) {
    const uint8_t *ptr = (const uint8_t *) p;
    if (len > 256U)
    {
        return 0;
    }
    uint8_t crc = 0xFF;
    uint8_t crcLo = 0xFF;
    do
    {
        uint8_t i = crc ^ *ptr++;
        crc = crcLo ^ (uint8_t) (auchCRCHi[i]);
        crcLo = (uint8_t) (auchCRCLo[i]);
    } while (--len);

    return ((crc << 8) | crcLo);
}


void terminalCreator::openSerialPort(Ui::guiUI *m_ui)
{
    const terminalSettings::Settings p = m_settings->settings();
    m_serial->setPortName(p.name);
    m_serial->setBaudRate(p.baudRate);
    m_serial->setDataBits(p.dataBits);
    m_serial->setParity(p.parity);
    m_serial->setStopBits(p.stopBits);
    m_serial->setReadBufferSize(0);
    if (m_serial->open(QIODevice::ReadWrite))
    {
        m_console->setEnabled(true);
        m_console->setLocalEchoEnabled(p.localEchoEnabled);
        m_ui->actionConnect->setEnabled(false);
        m_ui->actionDisconnect->setEnabled(true);
        showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                          .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                          .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl),m_ui);
    }
    else
    {
        showStatusMessage(tr("Open error"),m_ui);
    }
}


void terminalCreator::changeTerminalSettingsHere(Ui::guiUI *m_ui)
{
    m_settings->updateSettings(m_ui);
}


void terminalCreator::showTerminalPortInfoHere(int idx,Ui::guiUI *m_ui)
{
    m_settings->showPortInfo(idx,m_ui);
}


void terminalCreator::checkTerminalCustomBaudRatePolicyHere(int idx,Ui::guiUI *m_ui)
{
   m_settings->checkCustomBaudRatePolicy(idx,m_ui);
}


void terminalCreator::checkTerminalCustomDevicePathPolicyHere(int idx,Ui::guiUI *m_ui)
{
   m_settings->checkCustomDevicePathPolicy(idx,m_ui);
}


void terminalCreator::closeSerialPort(Ui::guiUI *m_ui)
{
    if (m_serial->isOpen())
        m_serial->close();
    m_console->setEnabled(false);
    m_ui->actionConnect->setEnabled(true);
    m_ui->actionDisconnect->setEnabled(false);
    showStatusMessage(tr("Disconnected"),m_ui);
}


void terminalCreator::readData()
{
    static QByteArray header;
    static bool infoIsOld=false;
    uartFile receivedFile;

    header = m_serial->read(10);

    receivedFile.hStart=header[0];
    receivedFile.hAddr=((header.at(1) & 0xFF)<<8) | (header.at(2) & 0xFF);

    receivedFile.hCode=header[3];
    receivedFile.hLength=(header[7]<<24) | (header[6]<<16) | (header[5]<<8) | header [4];
    receivedFile.controlSumm=((header.at(8) & 0xFF)<<8) | (header.at(9) & 0xFF);

    if(receivedFile.hAddr!=0b1000000000000000)
    {
        header.clear();
        m_serial->clear();
    }
    else if(receivedFile.hAddr==0b1000000000000000)
    {
        m_console->appendPlainText("Received header в hex - "+header.toHex());
        m_console->appendPlainText("Received packet: Start - "+QString("0x%1").arg(receivedFile.hStart,2,16,QLatin1Char('0'))+";"
                                    " Addr - "+QString("0x%1").arg(receivedFile.hAddr,4,16,QLatin1Char('0'))+";"
                                    " Code - "+QString("0x%1").arg(receivedFile.hCode,2,16,QLatin1Char('0'))+";"
                                    " Length - "+QString("0x%1").arg(receivedFile.hLength,8,16,QLatin1Char('0'))+";"
                                    " Control summ - "+QString("0x%1").arg(receivedFile.controlSumm,2,16,QLatin1Char('0'))+";");


        if(receivedFile.hCode==0x11)
        {
            sendStatus();
        }

        else if(receivedFile.hCode==0x12)
        {
            if(!infoIsOld)
            {
                sendFile(receivedFile.hLength);
            }
            else{
                nothing();
            }
        }

        else if(receivedFile.hCode==0x13)
        {
            if(!infoIsOld)
            {
                sendEmptyFile(receivedFile.hLength);
            }
            else{
                nothing();
            }
        }
        else if(receivedFile.hCode==0x14)
        {
            m_console->appendPlainText("Received acception: Start - "+QString("0x%1").arg(receivedFile.hStart,2,16,QLatin1Char('0'))+";"
                                        " Address - "+QString("0x%1").arg(receivedFile.hAddr,4,16,QLatin1Char('0'))+";"
                                        " Code - "+QString("0x%1").arg(receivedFile.hCode,2,16,QLatin1Char('0'))+";"
                                        " Length - "+QString("0x%1").arg(receivedFile.hLength,8,16,QLatin1Char('0'))+";"
                                        " Control summ - "+QString("0x%1").arg(receivedFile.controlSumm,2,16,QLatin1Char('0'))+";");

            QThread::msleep(1000);
            m_serial->waitForReadyRead(1000);

            static QByteArray infoReceived;
            infoReceived.clear();
            infoReceived.append(header[8]);
            infoReceived.append(header[9]);
            receivedFile.hLength=(header[7]<<8) | (header[6]);
            infoReceived.append(m_serial->read(receivedFile.hLength-2));
            QByteArray controlSummMassive  = m_serial->read(2);
            readInfo(infoReceived.data());

            QFile file(terminalFilePath+"info_file.xml");
            file.open(QIODevice::ReadOnly);
            QByteArray info = file.readAll();
            file.close();

            if(infoReceived==info){
                m_console->appendPlainText("Received file is correct");
                infoIsOld=true;
            }
            m_console->appendPlainText(controlSummMassive.toHex()+" - Control summ");
        }
        else if(receivedFile.hCode==0x11)
        {
            m_console->appendPlainText("Received errors: Start - "+QString("0x%1").arg(receivedFile.hStart,2,16,QLatin1Char('0'))+";"
                                        " Address - "+QString("0x%1").arg(receivedFile.hAddr,4,16,QLatin1Char('0'))+";"
                                        " Code - "+QString("0x%1").arg(receivedFile.hCode,2,16,QLatin1Char('0'))+";"
                                        " Length - "+QString("0x%1").arg(receivedFile.hLength,8,16,QLatin1Char('0'))+";"
                                        " Control summ - "+QString("0x%1").arg(receivedFile.controlSumm,2,16,QLatin1Char('0'))+";");
            QThread::msleep(1000);
            static QByteArray massiveReceived;
            massiveReceived.clear();
            massiveReceived.append(header[4]);
            massiveReceived.append(header[5]);
            m_console->appendPlainText("Control summ - "+QString("0x%1").arg(receivedFile.controlSumm,2,16,QLatin1Char('0')));
        }
    }
}


void terminalCreator::readInfo(QByteArray fileData)
{
    QXmlStreamReader xml(fileData);
    while (!xml.atEnd())
    {
        xml.readNext();
        QString stringAttributes;
        if(xml.attributes().hasAttribute("Class"))
            stringAttributes.append(" Class - "+xml.attributes().value("Class").toString()+"; ");
        if(xml.attributes().hasAttribute("id"))
            stringAttributes.append(" Id - "+xml.attributes().value("id").toString()+"; ");
        if(xml.attributes().hasAttribute("filename"))
            stringAttributes.append(" File name- "+xml.attributes().value("filename").toString()+"; ");
        if(xml.attributes().hasAttribute("Info"))
            stringAttributes.append(" Info - "+xml.attributes().value("info").toString()+"; ");
        if(xml.attributes().hasAttribute("Value"))
            stringAttributes.append(" "+xml.attributes().value("Value").toString()+"; ");
        if(stringAttributes.size()>0)
            m_console->appendPlainText(stringAttributes);
    }
}


void terminalCreator::sendStatus(){
    static uartFile structStatus;
    structStatus.hStart = 0x3A;
    structStatus.hAddr = 1;
    structStatus.hCode = 0x4A;
    structStatus.hLength = 0;

    static QByteArray bytesStatus;
    bytesStatus.clear();

    bytesStatus.append(structStatus.hStart);
    bytesStatus.append(reinterpret_cast<const char*>(&structStatus.hAddr),sizeof(structStatus.hAddr));
    bytesStatus.append(structStatus.hCode);
    bytesStatus.append(reinterpret_cast<const char*>(&structStatus.hLength),sizeof(structStatus.hLength));
    structStatus.controlSumm = CRC256(bytesStatus, 8);
    bytesStatus.append(reinterpret_cast<const char*>(&structStatus.controlSumm),sizeof(structStatus.controlSumm));

    m_serial->write(bytesStatus);
    m_console->appendPlainText("Send answer: Star - "+QString("0x%1").arg(structStatus.hStart,2,16,QLatin1Char('0'))+";"
                                " Address - "+QString("0x%1").arg(structStatus.hAddr,4,16,QLatin1Char('0'))+";"
                                " Code - "+QString("0x%1").arg(structStatus.hCode,2,16,QLatin1Char('0'))+";"
                                " Length - "+QString("0x%1").arg(structStatus.hLength,8,16,QLatin1Char('0'))+";"
                                " Control summ - "+QString("0x%1").arg(structStatus.controlSumm,2,16,QLatin1Char('0'))+";");
}


void terminalCreator::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError)
    {
        emit closeSerialPortSignal();
    }
}


void terminalCreator::showStatusMessage(const QString &message,Ui::guiUI *m_ui)
{
    m_ui->statusBar->setText(message);
}


void terminalCreator::sendEmptyFile(int numfile)
{
    uartFile structEmptyFile;
    bool fileLengthIsAvalable = false;

    if(numfile == 1)
    {
        QFile file(terminalFilePath+"file1.xml");
        structEmptyFile.hLength = file.size();
        fileLengthIsAvalable=true;
    }
    else if(numfile == 3)
    {
        QFile file(terminalFilePath+"file3.xml");
        structEmptyFile.hLength = file.size();
        fileLengthIsAvalable=true;
    }
    else if(numfile == 4)
    {
        QFile file(terminalFilePath+"file4.xml");
        structEmptyFile.hLength = file.size();
        fileLengthIsAvalable=true;
    }
    else if(numfile == 5)
    {
        QFile file(terminalFilePath+"file5.xml");
        structEmptyFile.hLength = file.size();
        fileLengthIsAvalable=true;
    }
    else if(numfile == 8)
    {
        QFile file(terminalFilePath+"file8.xml");
        structEmptyFile.hLength = file.size();
        fileLengthIsAvalable=true;
    }
    else
    {
        nothing();
    }

    if(fileLengthIsAvalable)
    {
        structEmptyFile.hStart = 0x3A;
        structEmptyFile.hAddr = 1;
        structEmptyFile.hCode = 0x5A;


        static QByteArray bytesEmptyFile;
        bytesEmptyFile.clear();

        bytesEmptyFile.append(structEmptyFile.hStart);
        bytesEmptyFile.append(reinterpret_cast<const char*>(&structEmptyFile.hAddr),sizeof(structEmptyFile.hAddr));
        bytesEmptyFile.append(structEmptyFile.hCode);
        bytesEmptyFile.append(reinterpret_cast<const char*>(&structEmptyFile.hLength),sizeof(structEmptyFile.hLength));
        structEmptyFile.controlSumm = CRC256(bytesEmptyFile,8);
        bytesEmptyFile.append(reinterpret_cast<const char*>(&structEmptyFile.controlSumm),sizeof(structEmptyFile.controlSumm));

        m_serial->write(bytesEmptyFile);
        m_console->appendPlainText("Send length: Start - "+QString("0x%1").arg(structEmptyFile.hStart,2,16,QLatin1Char('0'))+";"
                                    " Address - "+QString("0x%1").arg(structEmptyFile.hAddr,4,16,QLatin1Char('0'))+";"
                                    " Code - "+QString("0x%1").arg(structEmptyFile.hCode,2,16,QLatin1Char('0'))+";"
                                    " Length - "+QString("0x%1").arg(structEmptyFile.hLength,8,16,QLatin1Char('0'))+";"
                                    " Control summ - "+QString("0x%1").arg(structEmptyFile.controlSumm,2,16,QLatin1Char('0'))+";");
    }
}



void terminalCreator::sendFile(int numfile)
{
    static uartFile structFullFile;
    bool fileIsAvalable = false;
    static bool file5 = 0;
    static bool file4 = 0;
    static bool file3 = 0;
    static bool file_info = 0;
    static bool file8 = 0;

    if(numfile == 1)
    {
        QFile file(terminalFilePath+"file_info.xml");
        file.open(QIODevice::ReadOnly);
        structFullFile.hLength = file.size();
        file.close();
        fileIsAvalable=true;
        t_ui->piFileButton->setChecked(1);
        file_info=1;

    }
    else if(numfile == 3)
    {
        QFile file(terminalFilePath+"file3.xml");
        file.open(QIODevice::ReadOnly);
        structFullFile.hLength = file.size();
        file.close();
        fileIsAvalable=true;
        t_ui->ntiFileButton->setChecked(1);
        file3=1;
    }
    else if(numfile == 4)
    {
        QFile file(terminalFilePath+"file4.xml");
        file.open(QIODevice::ReadOnly);
        structFullFile.hLength = file.size();
        file.close();
        fileIsAvalable=true;
        t_ui->blaFileButton->setChecked(1);
        file4=1;
    }
    else if(numfile == 5)
    {
        QFile file(terminalFilePath+"file5.xml");
        file.open(QIODevice::ReadOnly);
        structFullFile.hLength = file.size();
        file.close();
        fileIsAvalable=true;
        t_ui->meteoFileButton->setChecked(1);
        file5=1;
    }
    else if(numfile == 8)
    {
        QFile file(terminalFilePath+"file8.xml");
        file.open(QIODevice::ReadOnly);
        structFullFile.hLength = file.size();
        file.close();
        fileIsAvalable=true;
        t_ui->psvFileButton->setChecked(1);
        file8=1;
    }
    else
    {
        nothing();
    }

    if(fileIsAvalable)
    {
        structFullFile.hStart = 0x3A;
        structFullFile.hAddr = 1;
        structFullFile.hCode = 0x5B;

        static QByteArray bytesFullFile;
        bytesFullFile.clear();

        bytesFullFile.append(structFullFile.hStart);
        bytesFullFile.append(reinterpret_cast<const char*>(&structFullFile.hAddr),sizeof(structFullFile.hAddr));
        bytesFullFile.append(structFullFile.hCode);
        bytesFullFile.append(reinterpret_cast<const char*>(&structFullFile.hLength),sizeof(structFullFile.hLength));
        structFullFile.controlSumm = CRC(bytesFullFile,structFullFile.hLength+8);
        bytesFullFile.append(reinterpret_cast<const char*>(&structFullFile.controlSumm),sizeof(structFullFile.controlSumm));

        m_serial->write( bytesFullFile);

        m_console->appendPlainText("Send file: Start - "+QString("0x%1").arg(structFullFile.hStart,2,16,QLatin1Char('0'))+";"
                                    " Address - "+QString("0x%1").arg(structFullFile.hAddr,4,16,QLatin1Char('0'))+";"
                                    " Code - "+QString("0x%1").arg(structFullFile.hCode,2,16,QLatin1Char('0'))+";"
                                    " Length - "+QString("0x%1").arg(structFullFile.hLength,8,16,QLatin1Char('0'))+";"
                                    " Control summ - "+QString("0x%1").arg(structFullFile.controlSumm,2,16,QLatin1Char('0'))+";");
    }
    if(file3 && file4 && file5 && file8 && file_info){
        m_console->appendPlainText("All files was sent");
        timer->stop();
        timer->start();
    }
}


void terminalCreator::allFilesIsSentSlot(){
    t_ui->allFilesButton->setChecked(1);
}


void terminalCreator::nothing()
{
    static uartFile structNothing;
    structNothing.hStart = 0x3A;
    structNothing.hAddr = 1;
    structNothing.hCode = 0xA5;
    structNothing.hLength = 0;


    static QByteArray bytesNothing;
    bytesNothing.clear();

    bytesNothing.append(structNothing.hStart);
    bytesNothing.append(reinterpret_cast<const char*>(&structNothing.hAddr),sizeof(structNothing.hAddr));
    bytesNothing.append(structNothing.hCode);
    bytesNothing.append(reinterpret_cast<const char*>(&structNothing.hLength),sizeof(structNothing.hLength));
    structNothing.controlSumm = CRC256(bytesNothing,8);
    bytesNothing.append(reinterpret_cast<const char*>(&structNothing.controlSumm),sizeof(structNothing.controlSumm));

    m_serial->write( bytesNothing);

    m_console->appendPlainText("Sent nothing: Start - "+QString("0x%1").arg(structNothing.hStart,2,16,QLatin1Char('0'))+";"
                                " Address - "+QString("0x%1").arg(structNothing.hAddr,4,16,QLatin1Char('0'))+";"
                                " Code - "+QString("0x%1").arg(structNothing.hCode,2,16,QLatin1Char('0'))+";"
                                " Length - "+QString("0x%1").arg(structNothing.hLength,8,16,QLatin1Char('0'))+";"
                                " Control summ - "+QString("0x%1").arg(structNothing.controlSumm,2,16,QLatin1Char('0'))+";");

}
