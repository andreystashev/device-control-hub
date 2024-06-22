#include "buttonscreator.h"
#include "messages.h"


void buttonsCreator::targetButtons(QRadioButton* button[],Ui::guiUI* ui)
{
    int buttonsWidth = 37;

    for(int i = 0; i<actualTelemetricSize;i++){
        button[i] = new QRadioButton( ui->label);
        button[i]->setGeometry(500,100,150,30);
        button[i]->move(1600,buttonsWidth);
        button[i]->setStyleSheet("QRadioButton{font-size:17px;font:bold; border: 1px solid "+blackColor+"; color: "+blackColor+"}\
                                 QRadioButton::hover{background-color: "+greyColor+"; color: "+blackColor+"}\
                                 QRadioButton::checked{background-color: "+blackColor+"; color: "+whiteColor+"}\
                                 QRadioButton::indicator{background-color:transparent}");

        buttonsWidth+=29;
        button[i]->setCheckable(true);
        button[i]->setCursor(QCursor(Qt::PointingHandCursor));
        button[i]->setObjectName(QString::number(i));
        button[i]->setText("Target "+QString::number(i+1));

    }
}


void buttonsCreator::chartScope(QLabel *cells[], QLabel *cellsInfo[], QLabel *place, const QString nameMassive[], int elementsCount, int x, int y, int width)
{
        QLabel *PlaceScroll = new QLabel();
        QScrollArea *scrollArea = new QScrollArea(place);
        scrollArea->setWidget(PlaceScroll);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    static int chartScopeCounter = 0;
    for(int i=0;i<elementsCount;i++)
    {
        cells[i] = new QLabel(PlaceScroll);
        cells[i]->setText(nameMassive[i]);
        cells[i]->setGeometry(QRect(0,0,width,36));
        cells[i]->move(0,chartScopeCounter);
        cells[i]->setStyleSheet("QLabel{font-size:16px;font:bold; border: 1px solid "+blackColor+"; color: "+blackColor+"}\
                                                       QLabel::hover{background-color: "+blackColor+"; color: "+whiteColor+"}");

        cellsInfo[i] = new QLabel(PlaceScroll);
        cellsInfo[i]->setNum(0);
        cellsInfo[i]->setGeometry(QRect(0,0,150,36));
        cellsInfo[i]->move(width-1,chartScopeCounter);
        cellsInfo[i]->setStyleSheet("QLabel{font-size:16px;font:bold; border: 1px solid "+blackColor+"; color: "+blackColor+"}\
                                    QLabel::hover{background-color: "+blackColor+"; color: "+whiteColor+"}");
        chartScopeCounter+=35;
    }
    PlaceScroll->move(x,y);
    PlaceScroll->resize(width+150,chartScopeCounter+1);
    scrollArea->resize(width+170,900);

    chartScopeCounter = 0;

}



void buttonsCreator::photoButton(unsigned int time, networkCreator* sock)
{
        static int packetNumber = 0;
        messageObject.id = packetNumber;
        messageObject.timeReturn = time;
        messageObject.timeCommand = time;
        messageObject.commandCode = 1;
        messageObject.commandParam = 0;
        commandContainer.clear();
        commandContainer.append(reinterpret_cast<char *>(&messageObject),sizeof(messageObject));
        sock->socket->write(commandContainer);
        packetNumber +=1;
}


void buttonsCreator::returnButton(unsigned int time, networkCreator* sock)
{
    static int packetNumber = 0;
    messageObject.id = packetNumber;
    messageObject.timeReturn = time;
    messageObject.timeCommand = time;
    messageObject.commandCode = 2;
    messageObject.commandParam = 0x00000001;
    commandContainer.clear();
    commandContainer.append(reinterpret_cast<char *>(&messageObject),sizeof(messageObject));
    sock->socket->write(commandContainer);
    packetNumber +=1;
}


void buttonsCreator::landingButton(unsigned int time, networkCreator* sock)
{
    static int packetNumber = 0;
    messageObject.id = packetNumber;
    messageObject.timeReturn = time;
    messageObject.timeCommand = time;
    messageObject.commandCode = 3;
    messageObject.commandParam = 0;
    commandContainer.clear();
    commandContainer.append(reinterpret_cast<char *>(&messageObject),sizeof(messageObject));
    sock->socket->write(commandContainer);
    packetNumber +=1;
}


void buttonsCreator::detonateButton(unsigned int time, networkCreator* sock)
{
    static int packetNumber = 0;
    messageObject.id = packetNumber;
    messageObject.timeReturn = time;
    messageObject.timeCommand = time;
    messageObject.commandCode = 4;
    messageObject.commandParam = 0;
    commandContainer.clear();
    commandContainer.append(reinterpret_cast<char *>(&messageObject),sizeof(messageObject));
    sock->socket->write(commandContainer);
    packetNumber +=1;
}




