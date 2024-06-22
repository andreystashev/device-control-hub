#ifndef FILECREATOR_H
#define FILECREATOR_H
#include <QTcpServer>
#include <QDateTime>

#include "messages.h"
#include "ui_guicreator.h"


class guiCreator;

class fileCreator: public QObject
{
public:
    QString fileDateTime;
    unsigned int flightID;

    fileCreator(guiCreator* pFileBlock,QObject *parent=nullptr);
    guiCreator* guiFile;
    fileCreator();
    void showFileHeaderAuto(QString filename, Ui::guiUI *ui);
private:
    QDateTime fileTime;
    Header fileInformation;
    ActualTelemetricMessage writeMessage;
    ActualTelemetricMessage firstMessage;
    ActualTelemetricMessage lastMessage;


public slots:
    void writeDataSlot();
    void writeDataNewMassivesSlot();
    void readDataNewMassivesSlot();
    void writeDataBDMassivesSlot();
};


QDataStream &operator <<(QDataStream &out, const Header &any);
QDataStream &operator <<(QDataStream &out, const ActualTelemetricMessage &any);
QDataStream &operator >>(QDataStream &in, const Header &any);
QDataStream &operator >>(QDataStream &in, const ActualTelemetricMessage &any);






#endif // FILECREATOR_H
