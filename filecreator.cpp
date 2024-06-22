#include <QTcpSocket>
#include <QFile>
#include <QDataStream>
#include <QFileInfo>
#include <QDir>
#include "filecreator.h"
#include "networkcreator.h"


QDataStream &operator >>(QDataStream &in, const Header &any)
{
    in >> (uint32_t&)any.messageTimestamp;
    in >> (uint32_t&)any.transmissionStartTime;
    in >> (uint32_t&)any.dataId;
    in >> (uint32_t&)any.messageCount;
    in >> (uint32_t&)any.reserve;
    in >> (uint32_t&)any.reserve2;
    in >> (uint32_t&)any.totalFlightDuration;
    in >> (uint32_t&)any.flightIdentifier;
    in >> (uint32_t&)any.eventStartPosition;
    in >> (uint32_t&)any.stateVectorStartPosition;
    in >> (uint32_t&)any.groupCompositionData;
    return in;
};


QDataStream &operator >>(QDataStream &in, ActualTelemetricMessage &any)
{
    in >> (uint16_t &)any.packageIdentifier;
    in >> (uint32_t &)any.counter;
    in >> (uint32_t &)any.missionIdentifier;
    in >> (uint8_t  &)any.subscriberNumber;
    in >> (uint8_t  &)any.groupNumber;
    in >> (uint8_t  &)any.statusA;
    in >> (uint8_t  &)any.reserveA;
    in >> (uint32_t &)any.powerOnTime;
    in >> (uint32_t &)any.navigationTime;
    in >> (uint16_t &)any.dataValidity;
    in >> (int16_t  &)any.rollAngle;
    in >> (int16_t  &)any.pitchAngle;
    in >> (int16_t  &)any.headingAngle;
    in >> (int32_t  &)any.northSpeed;
    in >> (int32_t  &)any.eastSpeed;
    in >> (int32_t  &)any.verticalSpeed;
    in >> (uint32_t &)any.speedMagnitude;
    in >> (int32_t  &)any.latitude;
    in >> (int32_t  &)any.longitude;
    in >> (int32_t  &)any.altitude;
    in >> (int16_t  &)any.angularVelocityX;
    in >> (int16_t  &)any.angularVelocityY;
    in >> (int16_t  &)any.angularVelocityZ;
    in >> (int16_t  &)any.accelerationX;
    in >> (int16_t  &)any.accelerationY;
    in >> (int16_t  &)any.accelerationZ;
    in >> (uint32_t &)any.gpsTime;
    in >> (int32_t  &)any.ssLatitude;
    in >> (int32_t  &)any.ssLongitude;
    in >> (int32_t  &)any.ssAltitude;
    return in;
}


QDataStream &operator <<(QDataStream &out, const Header &any)
{
    out << any.messageTimestamp;
    out << any.transmissionStartTime;
    out << any.dataId;
    out << any.messageCount;
    out << any.reserve;
    out << any.reserve2;
    out << any.totalFlightDuration;
    out << any.flightIdentifier;
    out << any.eventStartPosition;
    out << any.stateVectorStartPosition;
    out << any.groupCompositionData;
    return out;
};


QDataStream &operator <<(QDataStream &out, const ActualTelemetricMessage &any)
{
    out << any.packageIdentifier;
    out << any.counter;
    out << any.missionIdentifier;
    out << any.subscriberNumber;
    out << any.groupNumber;
    out << any.statusA;
    out << any.reserveA;
    out << any.powerOnTime;
    out << any.navigationTime;
    out << any.dataValidity;
    out << any.rollAngle;
    out << any.pitchAngle;
    out << any.headingAngle;
    out << any.eastSpeed;
    out << any.northSpeed;
    out << any.verticalSpeed;
    out << any.speedMagnitude;
    out << any.latitude;
    out << any.longitude;
    out << any.altitude;
    out << any.angularVelocityX;
    out << any.angularVelocityY;
    out << any.angularVelocityZ;
    out << any.accelerationX;
    out << any.accelerationY;
    out << any.accelerationZ;
    out << any.gpsTime;
    out << any.ssLatitude;
    out << any.ssLongitude;
    out << any.ssAltitude;
    return out;
}



fileCreator::fileCreator(guiCreator* fileCreator,QObject *parent): QObject(parent)
{
    guiFile=fileCreator;
    QString dateStr = fileTime.currentDateTime().toString("dd-MM-yy_hh-mm");
    fileDateTime = "flight_"+dateStr;
    flightID = fileTime.currentDateTime().toString("yyhhmmss").toInt();
};


void fileCreator::writeDataSlot()
{
    QFile file("flights/"+fileDateTime+"__"+QString::number(flightID)+"/"+fileDateTime+"__"+QString::number(flightID)+".bat");

    if(file.exists())
    {
        file.open(QIODevice::Append);
        QDataStream out(&file);
        if(writtenVector.size()>0)
        {
            for (int i = 0; i<writtenVector.size();i++)
            {
                ActualTelemetricMessage* t1 = reinterpret_cast<ActualTelemetricMessage*>(writtenVector[i].data());
                writeMessage  = *t1;
                out << writeMessage;
            }
            file.close();
            writtenVector.clear();
            writtenVector.squeeze();
        }
    }
    else
    {
        if(writtenVector.size() > 0)
        {
            ActualTelemetricMessage* pFirstMessage = reinterpret_cast<ActualTelemetricMessage*>(writtenVector[0].data());
            firstMessage  = *pFirstMessage;
            ActualTelemetricMessage* pLastMessage = reinterpret_cast<ActualTelemetricMessage*>(writtenVector[writtenVector.size() - 1].data());
            lastMessage  = *pLastMessage;
            fileInformation.messageTimestamp = fileTime.currentDateTime().toString("ddMMyyhhmm").toInt();
            fileInformation.transmissionStartTime = fileTime.currentDateTime().toString("ddMMyyhhmm").toInt();
            fileInformation.dataId = flightID;
            fileInformation.messageCount = writtenVector.size();
            fileInformation.reserve = firstMessage.groupNumber;
            fileInformation.reserve2 = 0;
            fileInformation.totalFlightDuration = lastMessage.powerOnTime;
            fileInformation.flightIdentifier = firstMessage.missionIdentifier;
            fileInformation.eventStartPosition = 0;
            fileInformation.stateVectorStartPosition = 0;
            fileInformation.groupCompositionData = 0;
        }

        file.open(QIODevice::WriteOnly);
        QDataStream out(&file);

        out << fileInformation;
        for (int i = 0; i<=writtenVector.size()-1;i++)
        {
            ActualTelemetricMessage* t1 = reinterpret_cast<ActualTelemetricMessage*>(writtenVector[i].data());
            writeMessage  = *t1;
            out << writeMessage;
        }
        file.close();
        writtenVector.clear();
        writtenVector.squeeze();
    }
}



void fileCreator::writeDataNewMassivesSlot()
{
    QFile file("flights/"+fileDateTime+"__"+QString::number(flightID)+"/"+fileDateTime+"__"+QString::number(flightID)+"NewMassives.bin");

    if(file.exists())
    {
        file.open(QIODevice::Append);
        for (const QByteArray& data : writtenVectorNewMassives)
        {
            file.write(data);
        }
        file.close();
        writtenVectorNewMassives.clear();
        writtenVectorNewMassives.squeeze();
    }

    else
    {
        if(writtenVector.size() > 0)
        {
            fileInformation.messageTimestamp = fileTime.currentDateTime().toString("ddMMyyhhmm").toInt();
            fileInformation.transmissionStartTime = fileTime.currentDateTime().toString("ddMMyyhhmm").toInt();
            fileInformation.dataId = 0;
            fileInformation.messageCount = writtenVectorNewMassives.size();
            fileInformation.reserve = 0;
            fileInformation.reserve2 = 0;
            fileInformation.totalFlightDuration = 0;
            fileInformation.flightIdentifier = 0;
            fileInformation.eventStartPosition = 0;
            fileInformation.stateVectorStartPosition = 0;
            fileInformation.groupCompositionData = 0;
        }

        file.open(QIODevice::WriteOnly);
        for (const QByteArray& data : writtenVectorNewMassives)
        {
            file.write(data);
        }
        file.close();
        writtenVectorNewMassives.clear();
        writtenVectorNewMassives.squeeze();
    }
}



void fileCreator::writeDataBDMassivesSlot()
{
    QFile file("flights/"+fileDateTime+"__"+QString::number(flightID)+"/"+fileDateTime+"__"+QString::number(flightID)+"BDMassives.bin");

    if(file.exists())
    {
        file.open(QIODevice::Append);
        for (const QByteArray& data : writtenVectorBDMassives)
        {
            file.write(data);
        }
        file.close();
        writtenVectorBDMassives.clear();
        writtenVectorBDMassives.squeeze();
    }

    else
    {
        if(writtenVector.size()>0)
        {

            fileInformation.messageTimestamp = fileTime.currentDateTime().toString("ddMMyyhhmm").toInt();
            fileInformation.transmissionStartTime = fileTime.currentDateTime().toString("ddMMyyhhmm").toInt();
            fileInformation.dataId = 0;
            fileInformation.messageCount = writtenVectorNewMassives.size();
            fileInformation.reserve = 0;
            fileInformation.reserve2 = 0;
            fileInformation.totalFlightDuration = 0;
            fileInformation.flightIdentifier = 0;
            fileInformation.eventStartPosition = 0;
            fileInformation.stateVectorStartPosition = 0;
            fileInformation.groupCompositionData = 0;
        }
        file.open(QIODevice::WriteOnly);
        for (const QByteArray& data : writtenVectorNewMassives)
        {
            file.write(data);
        }
        file.close();
        writtenVectorNewMassives.clear();
        writtenVectorNewMassives.squeeze();
    }
}



void fileCreator::readDataNewMassivesSlot(){
    QFile file("flights/"+fileDateTime+"__"+QString::number(flightID)+"/"+fileDateTime+"__"+QString::number(flightID)+"NewMassives.bin");
    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray buffer = file.readAll();
        file.close();
        QByteArray headerArray;
        QByteArray controlSummArray;
        QByteArray dataArray;

        int pos = 0;
        while (pos < buffer.size()) {
            int remaining = buffer.size() - pos;
            if (remaining < 6) {
                break;
            }
            headerArray = buffer.mid(pos, 6);
            uint16_t lenth = (headerArray[5] << 8) | headerArray[4];

            if (remaining < lenth + 8) {
                break;
            }
            dataArray = buffer.mid(pos + 6, lenth);
            controlSummArray = buffer.mid(pos + 6 + lenth, 2);
            pos += 6 + lenth + 2;
        }
    }

}


void fileCreator::showFileHeaderAuto(QString filename, Ui::guiUI *ui){

    ui->textStatus->clear();
    QFile file("flights/"+filename);

    if(!file.open(QIODevice::ReadOnly))
    {
        ui->textStatus->append("Error open file");
    }

    QDataStream in(&file);
    Header flying;
    in >> flying;
    ui->textStatus->append("Reviewing the file: "
                           "\n" + filename + "\n\
                           \nDate and time of file recording - " + QString::number(flying.messageTimestamp) + "\
                           \nStart time of transmission - " + QString::number(flying.transmissionStartTime) + "\
                           \nData identifier - " + QString::number(flying.dataId) + "\
                           \nNumber of records in the file - " + QString::number(flying.messageCount) + "\
                           \nReserved - " + QString::number(flying.reserve) + "\
                           \nReserved - " + QString::number(flying.reserve2) + "\
                           \nTotal flight duration - " + QString::number(flying.totalFlightDuration) + "\
                           \nFlight identifier - " + QString::number(flying.flightIdentifier) + "\
                           \nEvent start position - " + QString::number(flying.eventStartPosition) + "\
                           \nState vector start position - " + QString::number(flying.stateVectorStartPosition) + "\
                           \nGroup composition data - " + QString::number(flying.groupCompositionData)
                           );
    file.close();
};



