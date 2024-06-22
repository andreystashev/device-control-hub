#include "messages.h"
#include <QLabel>
#include <QRadioButton>
#include "qcustomplot.h"

void changeUartTable(double (&telemetricMassiveActual)[actualTelemetricSize][devicesCount], ActualUartMessage* UdetachedMessage) {
    telemetricMassiveActual[0][0] = static_cast<double>(UdetachedMessage->packageIdentifier);
    telemetricMassiveActual[1][0] = static_cast<double>(UdetachedMessage->counter);
    telemetricMassiveActual[2][0] = static_cast<double>(UdetachedMessage->missionIdentifier);
    telemetricMassiveActual[3][0] = static_cast<double>(UdetachedMessage->subscriberNumber);
    telemetricMassiveActual[4][0] = static_cast<double>(UdetachedMessage->groupNumber);
    telemetricMassiveActual[5][0] = static_cast<double>(UdetachedMessage->statusA);
    telemetricMassiveActual[6][0] = static_cast<double>(UdetachedMessage->reserveA);
    telemetricMassiveActual[7][0] = static_cast<double>(UdetachedMessage->powerOnTime) * 0.001;
    telemetricMassiveActual[8][0] = static_cast<double>(UdetachedMessage->navigationTime) * 0.001;
    telemetricMassiveActual[9][0] = static_cast<double>(UdetachedMessage->dataValidity);
    telemetricMassiveActual[10][0] = static_cast<double>(UdetachedMessage->rollAngle) * 0.01;
    telemetricMassiveActual[11][0] = 360.0 + static_cast<double>(UdetachedMessage->headingAngle) * 0.01;
    telemetricMassiveActual[12][0] = static_cast<double>(UdetachedMessage->eastSpeed) * 0.01;
    telemetricMassiveActual[13][0] = static_cast<double>(UdetachedMessage->northSpeed) * 0.01;
    telemetricMassiveActual[14][0] = static_cast<double>(UdetachedMessage->verticalSpeed) * 0.01;
    telemetricMassiveActual[15][0] = static_cast<double>(UdetachedMessage->speedMagnitude) * 0.01 * 3.6;
    telemetricMassiveActual[16][0] = static_cast<double>(UdetachedMessage->latitude) * 1e-07;
    telemetricMassiveActual[17][0] = static_cast<double>(UdetachedMessage->longitude) * 1e-07;
    telemetricMassiveActual[18][0] = static_cast<double>(UdetachedMessage->altitude) * 0.01;
    telemetricMassiveActual[19][0] = static_cast<double>(UdetachedMessage->angularVelocityX) * 0.1;
    telemetricMassiveActual[20][0] = static_cast<double>(UdetachedMessage->angularVelocityY) * 0.1;
    telemetricMassiveActual[21][0] = static_cast<double>(UdetachedMessage->angularVelocityZ) * 0.1;
    telemetricMassiveActual[22][0] = static_cast<double>(UdetachedMessage->accelerationX) * 0.001;
    telemetricMassiveActual[23][0] = static_cast<double>(UdetachedMessage->accelerationY) * 0.001;
    telemetricMassiveActual[24][0] = static_cast<double>(UdetachedMessage->accelerationZ) * 0.001;
    telemetricMassiveActual[25][0] = static_cast<double>(UdetachedMessage->gpsTime) * 0.001;
    telemetricMassiveActual[26][0] = static_cast<double>(UdetachedMessage->ssLatitude) * 1e-07;
    telemetricMassiveActual[27][0] = static_cast<double>(UdetachedMessage->ssLongitude) * 1e-07;
    telemetricMassiveActual[28][0] = static_cast<double>(UdetachedMessage->ssAltitude) * 0.01;
    telemetricMassiveActual[29][0] = static_cast<double>(UdetachedMessage->reserved) * 0.01;
}

void changeSocketTable(double (&telemetricMassiveActual)[actualTelemetricSize][devicesCount], int objectName, ActualTelemetricMessage* detachedMessage)
{
    telemetricMassiveActual[0][objectName] = static_cast<double>(detachedMessage->packageIdentifier);
    telemetricMassiveActual[1][objectName] = static_cast<double>(detachedMessage->counter);
    telemetricMassiveActual[2][objectName] = static_cast<double>(detachedMessage->missionIdentifier);
    telemetricMassiveActual[3][objectName] = static_cast<double>(detachedMessage->subscriberNumber);
    telemetricMassiveActual[4][objectName] = static_cast<double>(detachedMessage->groupNumber);
    telemetricMassiveActual[5][objectName] = static_cast<double>(detachedMessage->statusA);
    telemetricMassiveActual[6][objectName] = static_cast<double>(detachedMessage->powerOnTime) * 0.001;
    telemetricMassiveActual[7][objectName] = static_cast<double>(detachedMessage->navigationTime) * 0.001;
    telemetricMassiveActual[8][objectName] = static_cast<double>(detachedMessage->dataValidity);
    telemetricMassiveActual[9][objectName] = static_cast<double>(detachedMessage->rollAngle) * 0.01;
    telemetricMassiveActual[10][objectName] = static_cast<double>(detachedMessage->pitchAngle) * 0.01;
    telemetricMassiveActual[11][objectName] = 360.0 + static_cast<double>(detachedMessage->headingAngle) * 0.01; // если отриц +360.
    telemetricMassiveActual[12][objectName] = static_cast<double>(detachedMessage->eastSpeed) * 0.01;
    telemetricMassiveActual[13][objectName] = static_cast<double>(detachedMessage->northSpeed) * 0.01;
    telemetricMassiveActual[14][objectName] = static_cast<double>(detachedMessage->verticalSpeed) * 0.01;
    telemetricMassiveActual[15][objectName] = static_cast<double>(detachedMessage->speedMagnitude) * 0.01 * 3.6;
    telemetricMassiveActual[16][objectName] = static_cast<double>(detachedMessage->latitude) * 1e-07;
    telemetricMassiveActual[17][objectName] = static_cast<double>(detachedMessage->longitude) * 1e-07;
    telemetricMassiveActual[18][objectName] = static_cast<double>(detachedMessage->altitude) * 0.01;
    telemetricMassiveActual[19][objectName] = static_cast<double>(detachedMessage->angularVelocityX) * 0.1;
    telemetricMassiveActual[20][objectName] = static_cast<double>(detachedMessage->angularVelocityY) * 0.1;
    telemetricMassiveActual[21][objectName] = static_cast<double>(detachedMessage->angularVelocityZ) * 0.1;
    telemetricMassiveActual[22][objectName] = static_cast<double>(detachedMessage->accelerationX) * 0.001;
    telemetricMassiveActual[23][objectName] = static_cast<double>(detachedMessage->accelerationY) * 0.001;
    telemetricMassiveActual[24][objectName] = static_cast<double>(detachedMessage->accelerationZ) * 0.001;
    telemetricMassiveActual[25][objectName] = static_cast<double>(detachedMessage->gpsTime) * 0.01;
    telemetricMassiveActual[26][objectName] = static_cast<double>(detachedMessage->ssLatitude) * 1e-07;
    telemetricMassiveActual[27][objectName] = static_cast<double>(detachedMessage->ssLongitude) * 1e-07;
    telemetricMassiveActual[28][objectName] = static_cast<double>(detachedMessage->ssAltitude) * 0.01;
    telemetricMassiveActual[29][objectName] = static_cast<double>(detachedMessage->reserveA);
}


void changeWideMassivesTable(QLabel *deviceFirstResults[10], QLabel *deviceSecondResults[10],
                    QLabel *deviceThirdResults[10], int deviceMassiveChanger, PacketReader* pPacketReaderMessage)
{
    if(pPacketReaderMessage->deviceFirstStruct.arrayId == deviceMassiveChanger){
        deviceFirstResults[0]->setNum(pPacketReaderMessage->deviceFirstStruct.arrayId);
        deviceFirstResults[1]->setNum(pPacketReaderMessage->deviceFirstStruct.messageLength);
        deviceFirstResults[2]->setNum(pPacketReaderMessage->deviceFirstStruct.arrayCount);
        deviceFirstResults[3]->setNum(pPacketReaderMessage->deviceFirstStruct.hours);
        deviceFirstResults[4]->setNum(pPacketReaderMessage->deviceFirstStruct.minutes);
        deviceFirstResults[5]->setNum(pPacketReaderMessage->deviceFirstStruct.seconds);
        deviceFirstResults[6]->setNum(pPacketReaderMessage->deviceFirstStruct.groupObjectsCount);
        deviceFirstResults[7]->setNum(pPacketReaderMessage->deviceFirstStruct.airObjectsCount);
        deviceFirstResults[8]->setNum(pPacketReaderMessage->deviceFirstStruct.airObjectsCount);
        deviceFirstResults[9]->setNum(pPacketReaderMessage->deviceFirstStruct.groundObjectsCount);

        deviceSecondResults[0]->setNum(pPacketReaderMessage->deviceSecondStruct.arrayId);
        deviceSecondResults[1]->setNum(pPacketReaderMessage->deviceSecondStruct.messageLength);
        QString lat = QString::number(pPacketReaderMessage->deviceSecondStruct.latitude*1e-07,'f',8);
        deviceSecondResults[2]->setText(lat);
        QString lon = QString::number(pPacketReaderMessage->deviceSecondStruct.longitude*1e-07,'f',8);
        deviceSecondResults[3]->setText(lon);
        deviceSecondResults[4]->setNum(double(pPacketReaderMessage->deviceSecondStruct.barometricHeight*0.01));
        deviceSecondResults[5]->setNum(double(pPacketReaderMessage->deviceSecondStruct.geodesicHeight*0.01));
        deviceSecondResults[6]->setNum(pPacketReaderMessage->deviceSecondStruct.trueSpeed*0.01);
        deviceSecondResults[7]->setNum(pPacketReaderMessage->deviceSecondStruct.trackSpeed*0.01);
        deviceSecondResults[8]->setNum(pPacketReaderMessage->deviceSecondStruct.heading*0.01);
        deviceSecondResults[9]->setNum(pPacketReaderMessage->deviceSecondStruct.trackAngle*0.01);

        deviceThirdResults[0]->setNum(pPacketReaderMessage->deviceThirdStruct.arrayId);
        deviceThirdResults[1]->setNum(pPacketReaderMessage->deviceThirdStruct.messageLength);
        deviceThirdResults[2]->setNum(pPacketReaderMessage->deviceThirdStruct.batteryStatus);
        deviceThirdResults[3]->setNum(pPacketReaderMessage->deviceThirdStruct.flightRange);
        deviceThirdResults[4]->setNum(pPacketReaderMessage->deviceThirdStruct.payloadType);
        deviceThirdResults[5]->setNum(pPacketReaderMessage->deviceThirdStruct.sensorType);
        deviceThirdResults[6]->setNum(pPacketReaderMessage->deviceThirdStruct.taskCompletionStatus);
        deviceThirdResults[7]->setNum(pPacketReaderMessage->deviceThirdStruct.systemFailures);
        deviceThirdResults[8]->setNum(pPacketReaderMessage->deviceThirdStruct.ownObjectNumber);
        deviceThirdResults[9]->setNum(pPacketReaderMessage->deviceThirdStruct.objectSerialNumber);
    }
}


void graphFileShow(bool smallGraph,int objectName,QCustomPlot * smallFilePlots[actualTelemetricSize], QVector<ActualTelemetricMessage> & fileReadVector, int i){
    if(smallGraph==false)
    {
        if (objectName == 0) {
                    smallFilePlots[objectName]->graph(0)->addData(fileReadVector[i].powerOnTime, fileReadVector[i].packageIdentifier);
                }
                if (objectName == 1) {
                    smallFilePlots[objectName]->graph(0)->addData(fileReadVector[i].powerOnTime, fileReadVector[i].counter);
                }
                if (objectName == 2) {
                    smallFilePlots[objectName]->graph(0)->addData(fileReadVector[i].powerOnTime, fileReadVector[i].missionIdentifier);
                }
                if (objectName == 3) {
                    smallFilePlots[objectName]->graph(0)->addData(fileReadVector[i].powerOnTime, fileReadVector[i].subscriberNumber);
                }
                if (objectName == 4) {
                    smallFilePlots[objectName]->graph(0)->addData(fileReadVector[i].powerOnTime, fileReadVector[i].groupNumber);
                }
                if (objectName == 5) {
                    smallFilePlots[objectName]->graph(0)->addData(fileReadVector[i].powerOnTime, fileReadVector[i].statusA);
                }
                if (objectName == 6) {
                    smallFilePlots[objectName]->graph(0)->addData(fileReadVector[i].powerOnTime, fileReadVector[i].reserveA);
                }
                if (objectName == 7) {
                    smallFilePlots[objectName]->graph(0)->addData(fileReadVector[i].powerOnTime, fileReadVector[i].powerOnTime);
                }
                if (objectName == 8) {
                    smallFilePlots[objectName]->graph(0)->addData(fileReadVector[i].powerOnTime, fileReadVector[i].navigationTime);
                }
                if (objectName == 9) {
                    smallFilePlots[objectName]->graph(0)->addData(fileReadVector[i].powerOnTime, fileReadVector[i].dataValidity);
                }
                if (objectName == 10) {
                    smallFilePlots[objectName]->graph(0)->addData(fileReadVector[i].powerOnTime, fileReadVector[i].rollAngle);
                }
                if (objectName == 29) {
                    smallFilePlots[objectName]->graph(0)->addData(fileReadVector[i].powerOnTime, fileReadVector[i].ssAltitude);
                }
    }
    else if(smallGraph==true){

        if (objectName == 0) {
                    smallFilePlots[objectName]->graph(0)->addData(fileReadVector[i].powerOnTime, fileReadVector[i].packageIdentifier);
                }
                if (objectName == 1) {
                    smallFilePlots[objectName]->graph(0)->addData(fileReadVector[i].powerOnTime, fileReadVector[i].counter);
                }
                if (objectName == 2) {
                    smallFilePlots[objectName]->graph(0)->addData(fileReadVector[i].powerOnTime, fileReadVector[i].missionIdentifier);
                }
                if (objectName == 3) {
                    smallFilePlots[objectName]->graph(0)->addData(fileReadVector[i].powerOnTime, fileReadVector[i].subscriberNumber);
                }
                if (objectName == 4) {
                    smallFilePlots[objectName]->graph(0)->addData(fileReadVector[i].powerOnTime, fileReadVector[i].groupNumber);
                }
                if (objectName == 5) {
                    smallFilePlots[objectName]->graph(0)->addData(fileReadVector[i].powerOnTime, fileReadVector[i].statusA);
                }
                if (objectName == 6) {
                    smallFilePlots[objectName]->graph(0)->addData(fileReadVector[i].powerOnTime, fileReadVector[i].reserveA);
                }
                if (objectName == 7) {
                    smallFilePlots[objectName]->graph(0)->addData(fileReadVector[i].powerOnTime, fileReadVector[i].powerOnTime);
                }
                if (objectName == 8) {
                    smallFilePlots[objectName]->graph(0)->addData(fileReadVector[i].powerOnTime, fileReadVector[i].navigationTime);
                }
                if (objectName == 9) {
                    smallFilePlots[objectName]->graph(0)->addData(fileReadVector[i].powerOnTime, fileReadVector[i].dataValidity);
                }
                if (objectName == 10) {
                    smallFilePlots[objectName]->graph(0)->addData(fileReadVector[i].powerOnTime, fileReadVector[i].rollAngle);
                }
                if (objectName == 29) {
                    smallFilePlots[objectName]->graph(0)->addData(fileReadVector[i].powerOnTime, fileReadVector[i].ssAltitude);
                }
    }
}


void systemFirst_MassiveTable(QLabel *systemFirstResults[10], systemFirst *systemFirst_obj)
{
    systemFirstResults[0]->setNum(systemFirst_obj->packetId);
    systemFirstResults[1]->setNum(double(systemFirst_obj->timeCounter));
    systemFirstResults[2]->setNum(systemFirst_obj->latitude);
    systemFirstResults[3]->setNum(systemFirst_obj->longitude);
    systemFirstResults[4]->setNum(systemFirst_obj->altitude);
    systemFirstResults[5]->setNum(systemFirst_obj->trueHeading);
    systemFirstResults[6]->setNum(systemFirst_obj->rollAngle);
    systemFirstResults[7]->setNum(systemFirst_obj->pitchAngle);
    systemFirstResults[8]->setNum(systemFirst_obj->northVelocity);
    systemFirstResults[9]->setNum(systemFirst_obj->eastVelocity);
}

void systemSecond_MassiveTable(QLabel *systemSecondResults[10], systemSecond *systemSecond_obj)
{
    systemSecondResults[0]->setNum(systemSecond_obj->packetId);
    systemSecondResults[1]->setNum(double(systemSecond_obj->timeCounter));
    systemSecondResults[2]->setNum(systemSecond_obj->stateWordPE.condition);
    systemSecondResults[3]->setNum(systemSecond_obj->stateWordPE.ready);
    systemSecondResults[4]->setNum(systemSecond_obj->stateWordPE.charge);
    systemSecondResults[5]->setNum(systemSecond_obj->stateWordPE.dutyRegime);
    systemSecondResults[6]->setNum(systemSecond_obj->stateWordPE.mainRegime);
    systemSecondResults[7]->setNum(systemSecond_obj->batteryLevel);
    systemSecondResults[8]->setNum(systemSecond_obj->batteryCapacity);
    systemSecondResults[9]->setNum(systemSecond_obj->workTime);
}

void systemThird_MassiveTable(QLabel *systemThirdResults[10],systemThird *systemThird_obj)
{
    systemThirdResults[0]->setNum(systemThird_obj->packetId);
    systemThirdResults[1]->setNum(double(systemThird_obj->timeCounter));
    systemThirdResults[2]->setNum(systemThird_obj->infoO.IOS);
    systemThirdResults[3]->setNum(systemThird_obj->infoO.take);
    systemThirdResults[4]->setNum(systemThird_obj->infoO.regimeO);
    systemThirdResults[5]->setNum(systemThird_obj->infoO.stateO);
    systemThirdResults[6]->setNum(systemThird_obj->infoO.V_TK);
    systemThirdResults[7]->setNum(systemThird_obj->infoO.signR);
    systemThirdResults[8]->setNum(systemThird_obj->infoO.reserve);
    systemThirdResults[9]->setNum(systemThird_obj->azimuth);
}



