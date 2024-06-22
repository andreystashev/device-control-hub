#include "guicreator.h"
#include "ui_guicreator.h"
#include "graphcreator.h"
#include "filecreator.h"
#include "playercreator.h"
#include "buttonscreator.h"
#include "terminalSettings.h"
#include "terminalCreator.h"
#include "maplight.h"
#include "showmassives.cpp"


graphCreator graphs;
playerCreator player;
terminalSettings terminals;
terminalCreator terminalsWindow;
buttonsCreator creator;

guiCreator::guiCreator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::guiUI)
{

    ui->setupUi(this);


    for (int i = 0; i <actualTelemetricSize;i++)
    {
        smallTelemetricInformation[i]=0;
        smallTelemetricButton[i]=0;
    }

    graphs.firstInitialize(ui);

    connect(ui->applyButton, SIGNAL(clicked()), this, SLOT(changeTerminalSettings()));
    connect(ui->serialPortInfoListBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &guiCreator::showTerminalPortInfo);
    connect(ui->baudRateBox,  QOverload<int>::of(&QComboBox::currentIndexChanged), this, &guiCreator::checkTerminalCustomBaudRatePolicy);
    connect(ui->serialPortInfoListBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &guiCreator::checkTerminalCustomDevicePathPolicy);
    connect(ui->actionConnect, &QPushButton::clicked, this, &guiCreator::openTerminalSerialPort);
    connect(ui->actionDisconnect, &QPushButton::clicked, this, &guiCreator::closeTerminalSerialPort);
    connect(&terminalsWindow, SIGNAL(closeSerialPortSignal()), this, SLOT(closeTerminalSerialPort()));

    ui->fileBigGraph->hide();

    connect(ui->flightHandConnect, SIGNAL(clicked()), this, SLOT(handConnect()));
    connect(ui->flightRechange, SIGNAL(clicked()), this, SLOT(regimeChoice()));
    connect(ui->flight, SIGNAL(clicked()), this, SLOT(flight()));
    connect(ui->ground, SIGNAL(clicked()), this, SLOT(ground()));
    connect(ui->readFile, SIGNAL(clicked()), this, SLOT(file()));
    connect(ui->flightszConnect, SIGNAL(clicked()), this, SLOT(telemetric()));
    connect(ui->menuRegimeFlight, SIGNAL(clicked()), this, SLOT(regime()));
    connect(ui->menuRegimeFile, SIGNAL(clicked()), this, SLOT(regime()));
    connect(ui->menuRegimeGround, SIGNAL(clicked()), this, SLOT(regime()));
    connect(ui->menuRegimeTelemetric, SIGNAL(clicked()), this, SLOT(regime()));
    connect(ui->menuFlightTelemetric, SIGNAL(clicked()), this, SLOT(flight()));
    connect(ui->menuGroundFile, SIGNAL(clicked()), this, SLOT(ground()));
    connect(ui->menuReference, SIGNAL(clicked()), this, SLOT(reference()));
    connect(ui->menuFlightReference, SIGNAL(clicked()), this, SLOT(reference()));
    connect(ui->menuTelemetricReference, SIGNAL(clicked()), this, SLOT(reference()));
    connect(ui->menuGroundReference, SIGNAL(clicked()), this, SLOT(reference()));
    connect(ui->menuFileReference, SIGNAL(clicked()), this, SLOT(reference()));
    connect(ui->menuReferenceRegime, SIGNAL(clicked()), this, SLOT(regime()));
    connect(ui->menuRemoteControl, SIGNAL(clicked()), this, SLOT(remoteControl()));
    connect(ui->menuRemoteControlTelemetric, SIGNAL(clicked()), this, SLOT(telemetric()));
    connect(ui->menuTerminal, SIGNAL(clicked()), this, SLOT(terminal()));
    connect(ui->menuTerminalRegime, SIGNAL(clicked()), this, SLOT(regime()));
    connect(ui->menuTestButton, SIGNAL(clicked()), this, SLOT(testSpace()));
    connect(ui->menuTestRegime, SIGNAL(clicked()), this, SLOT(regime()));
    connect(ui->menuRegimeChart, SIGNAL(clicked()), this, SLOT(regime()));
    connect(ui->menuChartButton, SIGNAL(clicked()), this, SLOT(chart()));
    connect(ui->menuChartButton_2, SIGNAL(clicked()), this, SLOT(chart2()));
    connect(ui->menuRegimeChart_2, SIGNAL(clicked()), this, SLOT(regime()));

    connect(ui->telemetricShowPhoto, SIGNAL(clicked()), this, SLOT(updatePhoto()));
    connect(ui->telemetricWriteButton, SIGNAL(clicked()), this, SLOT(writeData()));
    connect(ui->read, SIGNAL(clicked()), this, SLOT(read()));
    connect(ui->plusButton, SIGNAL(clicked()), this, SLOT(increaseGraph()));
    connect(ui->fileMaxButton, SIGNAL(clicked()), this, SLOT(increaseGraph()));
    connect(ui->minusButton, SIGNAL(clicked()), this, SLOT(decreaseGraph()));
    connect(ui->fileMinButton, SIGNAL(clicked()), this, SLOT(decreaseGraph()));
    connect(ui->closeIcon, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->minimizeIcon, SIGNAL(clicked()), this, SLOT(showNormal()));
    connect(&mDataTimerTrajectory, SIGNAL(timeout()), this, SLOT(trajectoryParamSlot()));
    connect(&mDataTimer, SIGNAL(timeout()), this, SLOT(warningSlot()));
    connect(&mDataTimer, SIGNAL(timeout()), this, SLOT(ServerTimeTelemetric()));
    connect(&mDataTimer, SIGNAL(timeout()), this, SLOT(smallTelemetricButtonView()));
    connect(&mDataTimerGraph, SIGNAL(timeout()), this, SLOT(newGraphSlot()));
    connect(&mDataTimerGraph, SIGNAL(timeout()), this, SLOT(graphsSlot()));
    mDataTimerGraph.start(10);
    mDataTimer.start(10);
    mDataTimerTrajectory.start(50);
    mWideDataTimer.start(10);

    telemetricButtonsCells(cell,fileCell,infoTelemetric,graphTelemetric,graphFileTelemetric);

    fileObj = new fileCreator(this);

    showPics();
    showdeviceButtons();
    showMassiveButtons();
    startServer();
    showFiledeviceButtons();
    graphs.telemetricTrajectory(ui);

    connect(this, SIGNAL(graphsFileSignal(QPushButton*,int,bool)), this, SLOT(graphsFileCreator(QPushButton*,int,bool)));
    StreamerThread *thread = new StreamerThread(this);
    connect(thread, SIGNAL(signalNouvelleImage(QByteArray)), this, SLOT(slotNouvelleImage(QByteArray)));
    thread->start();

    QTabWidget *tabWidget = new QTabWidget(ui->label);
    QTabWidget *tabWidget2 = new QTabWidget(ui->label_2);

    QLabel *deviceFirstMassiveLab = new QLabel();
    QLabel *deviceSecondMassiveLab = new QLabel();
    QLabel *deviceThirdMassiveLab = new QLabel();
    tabWidget->addTab(deviceFirstMassiveLab,"First device massive");
    tabWidget->addTab(deviceSecondMassiveLab,"Second device massive");
    tabWidget->addTab(deviceThirdMassiveLab,"Third device massive");


    QLabel *systemFirstMassiveLab = new QLabel();
    QLabel *systemSecondMassiveLab = new QLabel();
    QLabel *systemThirdMassiveLab = new QLabel();
    tabWidget2->addTab(systemFirstMassiveLab,"First system massive");
    tabWidget2->addTab(systemSecondMassiveLab,"Second system massive");
    tabWidget2->addTab(systemThirdMassiveLab,"Third system massive");

    tabWidget->setGeometry(0,0,1760,920);
    tabWidget2->setGeometry(0,0,1760,920);
    ui->label_2->setGeometry(80,80,1760,920);
    ui->label_2->setStyleSheet("color: "+blackColor+";font-size: 14px;font:bold;border: 1px solid  "+blackColor+"");
    ui->label->setGeometry(80,80,1760,920);
    ui->label->setStyleSheet("color: "+blackColor+";font-size: 16px;font:bold;border: 1px solid  "+blackColor+"");

    creator.chartScope(deviceFirstMassiveButton, deviceFirstMassiveResults, deviceFirstMassiveLab, deviceFirstNameArray, 10, 100, 100, 800);
    creator.chartScope(deviceSecondMassiveButton, deviceSecondMassiveResults, deviceSecondMassiveLab, deviceSecondNameArray, 10, 100, 100, 800);
    creator.chartScope(deviceThirdMassiveButton, deviceThirdMassiveResults, deviceThirdMassiveLab, deviceThirdNameArray, 10, 100, 100, 800);

    creator.chartScope(systemFirstMassiveButton, systemFirstMassiveResults, systemFirstMassiveLab, systemFirstNameMassive, 10, 100, 100, 800);
    creator.chartScope(systemSecondMassiveButton, systemSecondMassiveResults, systemSecondMassiveLab, systemSecondNameMassive, 10, 100, 100, 800);
    creator.chartScope(systemThirdMassiveButton, systemThirdMassiveResults, systemThirdMassiveLab, systemThirdNameMassive, 10, 100, 100, 800);

    creator.targetButtons(TargetButton,ui);

    wideSocketMassive = new wideSocket(this);
    wideSocketMassive->newConnect();
    connect(wideSocketMassive,SIGNAL(arrayWideByteSend(QByteArray*)),this,SLOT(wideMassiveSlot(QByteArray*)));

    wideSocketSettingsVoiceHalper = new wideSocket(this);
    wideSocketSettingsVoiceHalper->newConnectVoiceHalper();

    player.newConnect(ui);

    QString flightDir = "flights/" + fileObj->fileDateTime + "__" + QString::number(fileObj->flightID) + "/";
    if (!QDir(flightDir).exists())
    {
        QDir().mkdir(flightDir);
        for (int i = 0; i <= 2; i++)
        {
            QString subdir = flightDir + QString::number(i) + "/";
            QDir().mkdir(subdir);

            QTime currentTime = QTime::currentTime();
            QDate currentDate = QDate::currentDate();
            QPixmap pixmap(400, 400);
            pixmap.fill(Qt::black);
            QPainter painter(&pixmap);
            painter.setPen(Qt::white);
            painter.setFont(QFont("Arial", 12));
            QString timeString = currentTime.toString();
            QString dateString = currentDate.toString(Qt::SystemLocaleLongDate);
            QString dateTimeString = timeString + " \n" + dateString+ " \n Device "+QString::number(i+1);
            painter.drawText(pixmap.rect(), Qt::AlignCenter, dateTimeString);
            painter.end();
            QString fileName = subdir + "intro.jpeg";
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly))
            {
                return;
            }
            bool success = pixmap.save(&file,"JPEG", 80);
            if (!success)
            {
            }
            file.close();
        }
    }
    fileObj->writeDataSlot();
    fileObj->writeDataNewMassivesSlot();
    fileObj->writeDataBDMassivesSlot();
    zMap.initMap(ui);
    ui->minTrajectory->hide();
    ui->maxTrajectory->hide();
    ui->bigMaxTrajectory->hide();
    ui->bigMinTrajectory->hide();
    ui->telemetricBigTrajectory->setLayout(ui->layoutMap_3);
    ui->telemetricSmallTrajectoryView->show();
    ui->textEditFilePath->append("files/");
}


guiCreator::~guiCreator()
{
    delete ui;
    server_status=0;
}

void guiCreator::openTerminalSerialPort(){
    terminalsWindow.openSerialPort(ui);
}
void guiCreator::closeTerminalSerialPort(){
    terminalsWindow.closeSerialPort(ui);
}

void guiCreator::changeTerminalSettings(){
    terminalsWindow.changeTerminalSettingsHere(ui);
}

void guiCreator::showTerminalPortInfo(int idx){
    terminalsWindow.showTerminalPortInfoHere(idx, ui);
}
void guiCreator::checkTerminalCustomBaudRatePolicy(int idx){
    terminalsWindow.checkTerminalCustomBaudRatePolicyHere(idx, ui);
}
void guiCreator::checkTerminalCustomDevicePathPolicy(int idx){
    terminalsWindow.checkTerminalCustomDevicePathPolicyHere(idx, ui);
}


void guiCreator::startServer()
{
    int ports[devicesCount] = {18002,18004,18006};
    for(int i = 0; i<devicesCount;i++){
        NetworkBServer[i] = new networkCreator();
        NetworkBServer[i]->setObjectName(QString::number(i));
        QObject::connect(NetworkBServer[i],SIGNAL(socketArrayNewByteSend(QByteArray*,uint16_t)),this,SLOT(fillNewInformationSlot(QByteArray*,uint16_t)));
        NetworkBServer[i]->listen(QHostAddress::Any, quint16(ports[i]));
    }
}


void guiCreator::startUart(char const command[]){
    for(int i = 0; i<devicesCount;i++){
        deviceSocket[i] = new networkCreator();//uart connection
        deviceSocket[i]->newConnect();
    }
    connect(deviceSocket[0],SIGNAL(arrayByteSend(QByteArray*)),this,SLOT(fillInformationSlot(QByteArray*)));
    connect(deviceSocket[0],SIGNAL(arrayNewByteSend(QByteArray*,uint16_t)),this,SLOT(fillNewInformationSlot(QByteArray*,uint16_t)));
    deviceSocket[0]->socket->write(command);
}


void guiCreator::on_userLink_clicked()
{
    QString userLink=ui->numTBA->toPlainText();
    QString userLinkString = "changed command "+userLink;
    ui->labelUserLink->setText("Sent command 'changed command"+userLink+"' ");
    std::string str = userLinkString.toStdString();
    char *array= new char[str.size()+1];
    std::copy(str.begin(),str.end(),array);
    startUart(array);
}


void guiCreator::fillNewInformationSlot(QByteArray *array,uint16_t idPacket)
{
    if(idPacket==0x1003){
      PsystemFirst_Massive_obj= reinterpret_cast<systemFirst*>(array->data());
      systemFirst_MassiveTable(systemFirstMassiveResults,PsystemFirst_Massive_obj);
      ui->console->clear();
      ui->console->append("systemFirst_Massive reveived - 0x1003 - "+QString::number(idPacket));
      ui->console->append("time counter: "+QString::number(PsystemFirst_Massive_obj->timeCounter));
      ui->console->append(array->toHex());
    }
    else{
        ui->console->clear();
        ui->console->append("Wrong massive: "+QString::number(idPacket));
        ui->console->append(array->toHex());
    }
    if(writtenVectorNewMassives.size()>1000){
        fileObj->writeDataNewMassivesSlot();
    }
}


void guiCreator::wideMassiveSlot(QByteArray *array)
{
        pPacketReaderMessage = reinterpret_cast<PacketReader*>(array->data());
        ui->console->clear();
        ui->console->append(deviceFirstMassiveResults[14]->text());
        ui->console->append(array->toHex());
        if(writtenVectorBDMassives.size()>1000){
            fileObj->writeDataBDMassivesSlot();
        }
}


void guiCreator::fillInformationSlot(QByteArray *array)
{
    ui->console->clear();
    ui->console->append(array->toHex());
    networkCreator *name = (networkCreator*) sender();
    if(ui->serverButton->isChecked())
    {
        if(writtenVector.size()>1000){
            fileObj->writeDataSlot();
        }
        detachedMessage = reinterpret_cast<ActualTelemetricMessage*>(array->data());
        changeCoordinatesSlot();
        changeSocketTable(telemetricMassiveActual,name->objectName().toInt(),detachedMessage);
    }

    else if(ui->uartButton->isChecked()){
        UdetachedMessage = reinterpret_cast<ActualUartMessage*>(array->data());
        changeCoordinatesSlot();
        changeUartTable(telemetricMassiveActual,UdetachedMessage);
    }
};


void guiCreator::ServerTimeTelemetric()//server 10000
{
    for(int i=0;i<actualTelemetricSize;i++){
        telemetricInformation[i]->setNum(telemetricMassiveActual[i][deviceChanger]);
    }
};


void guiCreator::graphsCreation(QCustomPlot *plot)//создание графиков по боковым кнопкам
{
    double key = telemetricMassiveActual[6][deviceChanger];
    plot->graph(0)->addData(key, telemetricMassiveActual[plot->objectName().toInt()][deviceChanger]);
    plot->graph(0)->rescaleValueAxis();
    plot->xAxis->setRange(key, 8, Qt::AlignRight);
    plot->yAxis->setLabel(QString::number(deviceChanger+1)+" Device");
    plot->replot();
};


void guiCreator::showdeviceButtons()//создание кнопок с номерами устройств
{
    int x = 0;
    for(int i=0;i<devicesCount;i++)
    {
        device[i] = new QRadioButton(ui->rocketPlace);
        device[i]->setCheckable(true);
        device[i]->setGeometry(QRect(0, 0, 121, 40));
        device[i]->move(x,0);
        device[i]->setCursor(QCursor(Qt::PointingHandCursor));
        device[i]->setObjectName(QString::number(i));
        device[i]->setText("Device "+QString::number(i+1));
        device[i]->setStyleSheet("QRadioButton{font-size:17px;font:bold; border: 1px solid "+blackColor+"; color: "+blackColor+"}\
                                                   QRadioButton::hover{background-color: "+greyColor+"; color: "+blackColor+"}\
                                                   QRadioButton::checked{background-color: "+blackColor+"; color: "+whiteColor+"}\
                                                   QRadioButton::indicator{background-color:transparent}");
        connect(device[i],SIGNAL(clicked()), this, SLOT(getdeviceButton()));
        x+=120;
    }
    ui->rocketPlace->setGeometry(QRect(20, 1020,x+1, 41));
}


void guiCreator::showMassiveButtons()//создание кнопок с номерами устройств
{
    int x = 0;
    for(int i=0;i<devicesCount;i++)
    {
        massivedeviceButton[i] = new QRadioButton(ui->massiveButtonsPlace);
        massivedeviceButton[i]->setCheckable(true);
        massivedeviceButton[i]->setGeometry(QRect(0, 0, 121, 40));
        massivedeviceButton[i]->move(x,0);
        massivedeviceButton[i]->setCursor(QCursor(Qt::PointingHandCursor));
        massivedeviceButton[i]->setObjectName(QString::number(i+1));
        massivedeviceButton[i]->setText("Device "+QString::number(i+1));
        massivedeviceButton[i]->setStyleSheet("QRadioButton{font-size:17px;font:bold; border: 1px solid "+blackColor+"; color: "+blackColor+"}\
                                                   QRadioButton::hover{background-color: "+greyColor+"; color: "+blackColor+"}\
                                                   QRadioButton::checked{background-color: "+blackColor+"; color: "+whiteColor+"}\
                                                   QRadioButton::indicator{background-color:transparent}");

        connect(massivedeviceButton[i],SIGNAL(clicked()), this, SLOT(getdeviceMassiveButton()));
        x+=120;
    }
    ui->massiveButtonsPlace->setGeometry(QRect(20, 1020,x+1, 41));
}

void guiCreator::getdeviceMassiveButton(){
    QRadioButton *deviceMassiveButton = (QRadioButton*) sender();
    deviceMassiveChanger = deviceMassiveButton->objectName().toInt();
}


void guiCreator::getdeviceButton(){
    QRadioButton *deviceButton = (QRadioButton*) sender();
    deviceChanger = deviceButton->objectName().toInt();
}


void guiCreator::on_sendMessage_clicked(){
    on_parachuteButton_clicked();

    telemetricInformation[0]->setText("message sent");
    for(int i=0;i<=11;i++)
    {
        deviceFirstMassiveResults[i]->setNum(i*(deviceFirstMassiveResults[i]->text().toInt()+i));
    }
}


void guiCreator::on_photoButton_clicked(){
    static uartFile structNothingToSendS;
    structNothingToSendS.hStart = 0x3A;
    structNothingToSendS.hAddr = 0b1111111111111111;
    structNothingToSendS.hCode = 0x12;
    uint16_t length = 0;
    structNothingToSendS.controlSumm = 2;

    static QByteArray bytesNothingToSendS;
    bytesNothingToSendS.clear();

    bytesNothingToSendS.append(structNothingToSendS.hStart);
    bytesNothingToSendS.append(reinterpret_cast<const char*>(&structNothingToSendS.hAddr),sizeof(structNothingToSendS.hAddr));
    bytesNothingToSendS.append(structNothingToSendS.hCode);
    bytesNothingToSendS.append(reinterpret_cast<const char*>(&length),sizeof(length));
    bytesNothingToSendS.append(reinterpret_cast<const char*>(&structNothingToSendS.controlSumm),sizeof(structNothingToSendS.controlSumm));
    deviceSocket[0]->socket->write(bytesNothingToSendS);
}


void guiCreator::on_returnPPMButton_clicked(){
    static uartFile structNothingToSendS;
    structNothingToSendS.hStart = 0x3A;
    structNothingToSendS.hAddr = 0x0020;
    structNothingToSendS.hCode = 0x03;
    structNothingToSendS.hLength = 0x0017;
    structNothingToSendS.controlSumm = 0x0017;
    uint16_t id=0x0611;
    uint16_t hLength = 0x0017;
    QByteArray bytesNothingToSendS2;
    bytesNothingToSendS2.clear();
    bytesNothingToSendS2.append(structNothingToSendS.hStart);
    bytesNothingToSendS2.append(reinterpret_cast<const char*>(&structNothingToSendS.hAddr),sizeof(structNothingToSendS.hAddr));
    bytesNothingToSendS2.append(structNothingToSendS.hCode);
    bytesNothingToSendS2.append(reinterpret_cast<const char*>(&hLength),sizeof(hLength));
    bytesNothingToSendS2.append(reinterpret_cast<const char*>(&id),sizeof(id));
    bytesNothingToSendS2.append(reinterpret_cast<const char*>(&structNothingToSendS.controlSumm),sizeof(structNothingToSendS.controlSumm));
    deviceSocket[0]->socket->write(bytesNothingToSendS2);

}


void guiCreator::on_parachuteButton_clicked(){

    static uartFile structNothingToSendS;
    structNothingToSendS.hStart = 0x3A;
    structNothingToSendS.hAddr = 0b1111111111111111;
    structNothingToSendS.hCode = 0x03;
    structNothingToSendS.hLength = 0;
    structNothingToSendS.controlSumm = 2;

    static QByteArray bytesNothingToSendS;
    bytesNothingToSendS.clear();
    bytesNothingToSendS.append(structNothingToSendS.hStart);
    bytesNothingToSendS.append(reinterpret_cast<const char*>(&structNothingToSendS.hAddr),sizeof(structNothingToSendS.hAddr));
    bytesNothingToSendS.append(structNothingToSendS.hCode);
    bytesNothingToSendS.append(reinterpret_cast<const char*>(&structNothingToSendS.hLength),sizeof(structNothingToSendS.hLength));
    bytesNothingToSendS.append(reinterpret_cast<const char*>(&structNothingToSendS.controlSumm),sizeof(structNothingToSendS.controlSumm));

    deviceSocket[0]->socket->write(bytesNothingToSendS);
}


void guiCreator::on_deadButton_clicked(){
    static uartFile structNothingToSendS;
    structNothingToSendS.hStart = 0x3A;
    structNothingToSendS.hAddr = 0b1111111111111111;
    structNothingToSendS.hCode = 0x09;
    uint16_t length = 0;
    structNothingToSendS.controlSumm = 2;

    static QByteArray bytesNothingToSendS;
    bytesNothingToSendS.clear();

    bytesNothingToSendS.append(structNothingToSendS.hStart);
    bytesNothingToSendS.append(reinterpret_cast<const char*>(&structNothingToSendS.hAddr),sizeof(structNothingToSendS.hAddr));
    bytesNothingToSendS.append(structNothingToSendS.hCode);
    bytesNothingToSendS.append(reinterpret_cast<const char*>(&length),sizeof(length));
    bytesNothingToSendS.append(reinterpret_cast<const char*>(&structNothingToSendS.controlSumm),sizeof(structNothingToSendS.controlSumm));
    deviceSocket[0]->socket->write(bytesNothingToSendS);
}


void guiCreator::slotNouvelleImage(QByteArray baImage)
{
    static int x=0;

    QPixmap pixImage;
    QImage image;

    if (!pixImage.loadFromData(baImage, "JPG"))
        return;
    image = pixImage.toImage();
    if (image.pixel(image.width() - 1, image.height() - 1 ) == 4286611584 &&
            image.pixel(image.width() / 2, image.height() - 1) == 4286611584  &&
            image.pixel(0, image.height() - 1) == 4286611584)
        return;

    ui->telemetricBigPhoto->setPixmap(pixImage);
    ui->telemetricBigPhoto->pixmap()->save("flights/"+fileObj->fileDateTime+"__"+QString::number(fileObj->flightID)+"/"+QString::number(deviceChanger)+"/"+QString::number(x)+"pic.jpeg");
    x++;
}


void guiCreator::on_minTrajectory_clicked(){
    ui->telemetricSmallTrajectoryView->setTransform(QTransform::fromScale(scX*=0.85,scY*=0.85));
}
void guiCreator::on_maxTrajectory_clicked(){
    ui->telemetricSmallTrajectoryView->setTransform(QTransform::fromScale(scX*=1.2,scY*=1.2));
}
void guiCreator::on_bigMinTrajectory_clicked(){
    ui->telemetricBigTrajectory->setTransform(QTransform::fromScale(scX*=0.85,scY*=0.85));
}
void guiCreator::on_bigMaxTrajectory_clicked(){
    ui->telemetricBigTrajectory->setTransform(QTransform::fromScale(scX*=1.2,scY*=1.2));
}

void guiCreator::on_minTrajectoryFile_clicked(){
    ui->fileSmallTrajectoryView->setTransform(QTransform::fromScale(scXF*=0.85,scYF*=0.85));
}

void guiCreator::on_maxTrajectoryFile_clicked(){
    ui->fileSmallTrajectoryView->setTransform(QTransform::fromScale(scXF*=1.2,scYF*=1.2));
}

void guiCreator::on_bigMinTrajectoryFile_clicked(){
    ui->fileBigTrajectory->setTransform(QTransform::fromScale(scXF*=0.85,scYF*=0.85));
}

void guiCreator::on_bigMaxTrajectoryFile_clicked(){
    ui->fileBigTrajectory->setTransform(QTransform::fromScale(scXF*=1.2,scYF*=1.2));
}


void guiCreator::showFiledeviceButtons()
{
    int x = 0;
    for(int i=0;i<devicesCount;i++)
    {
        filedevice[i] = new QRadioButton(ui->fileRocketPlace);
        filedevice[i]->setCheckable(true);
        filedevice[i]->setGeometry(QRect(0, 0, 121, 40));
        filedevice[i]->move(x,0);
        filedevice[i]->setCursor(QCursor(Qt::PointingHandCursor));
        filedevice[i]->setObjectName(QString::number(i));
        filedevice[i]->setText("Device "+QString::number(i+1));
        filedevice[i]->setStyleSheet("QRadioButton{font-size:17px;font:bold; border: 1px solid "+blackColor+"; color: "+blackColor+"}\
                                       QRadioButton::hover{background-color: "+greyColor+"; color: "+blackColor+"}\
                                       QRadioButton::checked{background-color: "+blackColor+"; color: "+whiteColor+"}\
                                       QRadioButton::indicator{background-color:transparent}");
        connect(filedevice[i],SIGNAL(clicked()), this, SLOT(getFiledeviceButton()));
        x+=120;
    }
    ui->fileRocketPlace->setGeometry(QRect(20, 1020,x+1, 41));
}


void guiCreator::getFiledeviceButton(){
    QRadioButton *deviceButton = (QRadioButton*) sender();
    if(deviceButton->isChecked())
    {
        filedeviceChanger = deviceButton->objectName().toInt();
        player.deviceName = QString::number(filedeviceChanger);
        player._imgIndex = 0;
        player.initializeStart();
    }
}


void guiCreator::regime(){
    ui->stackedWidget->setCurrentIndex(0);
}


void guiCreator::flight(){
    ui->stackedWidget->setCurrentIndex(1);
}


void guiCreator::ground(){
    showFiles();
    ui->stackedWidget->setCurrentIndex(2);
}


void guiCreator::file(){
    ui->stackedWidget->setCurrentIndex(3);
    loadFlightData(ui->textEditPort_2->toPlainText());
}


void guiCreator::telemetric(){
    ui->stackedWidget->setCurrentIndex(4);
}


void guiCreator::reference(){
    ui->stackedWidget->setCurrentIndex(5);
}


void guiCreator::remoteControl(){
    ui->stackedWidget->setCurrentIndex(6);
}


void guiCreator::terminal(){
    ui->stackedWidget->setCurrentIndex(7);
}


void guiCreator::testSpace(){
    ui->stackedWidget->setCurrentIndex(8);
}


void guiCreator::chart(){
    ui->stackedWidget->setCurrentIndex(9);
}


void guiCreator::chart2(){
    ui->stackedWidget->setCurrentIndex(10);
}


void guiCreator::read(){
    showFiles();
}


void guiCreator::writeData(){
    fileObj->writeDataSlot();
    showPics();
}


void guiCreator::updatePhoto(){
    showPics();
}

void guiCreator::increaseGraph(){
    graphs.maxGraph(ui);
    player.bigWindow();
}


void guiCreator::decreaseGraph(){
    graphs.minGraph(ui);
    player.smallWindow();
}


void guiCreator::regimeChoice()
{
    ui->flightPortWriter->hide();
    ui->flightStartConnect->hide();
    ui->flightLabel->hide();
    ui->scrollAreaIp->hide();
    ui->flightHandConnect->show();
    ui->flightszConnect->show();
}

void guiCreator::handConnect(){
    ui->scrollAreaIp->show();
    ui->flightHandConnect->hide();
    ui->flightszConnect->hide();
}


void guiCreator::graphWriter(QString name, double param, double time)
{
    ui->telemetricSmallGraph->xAxis->setLabel(name);
    ui->telemetricGraphInfo->setNum(param);
    graphs.graphCreation(param,time,ui);
}


void guiCreator::showFiles()
{
    ui->textStatus->clear();
    ui->textStatus->show();
    QDir dir("flights");
    QFileInfoList dirContent = dir.entryInfoList(QStringList());

    QRadioButton *cells[dirContent.size()-2];
    int x = 0;
    laylay = new QFormLayout();

    for(int i=2;i<dirContent.size();i++)
    {
        QFile file(dirContent[i].absoluteFilePath()+"/"+dirContent[i].fileName()+".bat");
        cells[i] = new QRadioButton(this);
        laylay->addRow(cells[i]);
        cells[i]->setText(dirContent[i].fileName());
        cells[i]->setCheckable(true);
        cells[i]->setGeometry(QRect(0, 0, 320, 30));
        cells[i]->move(0,x);
        cells[i]->setCursor(QCursor(Qt::PointingHandCursor));
        x+=29;

        cells[i]->setStyleSheet("QRadioButton{font-size:17px;font:bold; border: 1px solid "+blackColor+"; color: "+blackColor+"}\
                                QRadioButton::hover{background-color: "+greyColor+"; color: "+blackColor+"}\
                                QRadioButton::checked{background-color: "+blackColor+"; color: "+whiteColor+"}\
                                QRadioButton::indicator{background-color:transparent}");
        connect(cells[i],SIGNAL(clicked()), this, SLOT(getNum()));
        file.close();
    }
    fileWidgetForLayout->setLayout(laylay);
    ui->scrollAreaFile->setWidget(fileWidgetForLayout);
    ui->scrollAreaFile->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    fileWidgetForLayout->resize(320,x+1);
    ui->scrollAreaFile->setGeometry(QRect(623, 280,341, 477));
}


void guiCreator::getNum(){
    QPushButton *namecells = (QPushButton*) sender();
    if(namecells->isChecked())
    {
        ui->textEditPort_2->clear();
        fileObj->showFileHeaderAuto(namecells->text()+"/"+namecells->text()+".bat",ui);
        ui->textEditPort_2->append(namecells->text());
    }
}


void guiCreator::loadFlightData(QString DataId)
{
    if(DataId!=""){
    QFile telemetricFile("flights/"+DataId+"/"+DataId+".bat");
        QDataStream in(&telemetricFile);
        Header loadFileHeader;
        in >> loadFileHeader;
        player.folderName = DataId+"/";
        player.deviceName = QString::number(filedeviceChanger);
        player.initializeStart();
        fileReadVector.clear();
        while(!telemetricFile.atEnd())
        {
//            in>>fileReadMessage;
            fileReadVector.push_back(fileReadMessage);
        }
        telemetricFile.close();
    }
}


void guiCreator::fileTelemetricButtonsAction()
{
    QPushButton *graphAppendButton = (QPushButton*) sender();
    ui->fileSmallGraph->graph(0)->data()->clear();
    ui->fileSmallGraph->rescaleAxes();
    ui->fileSmallGraph->graph(0)->rescaleValueAxis();
    ui->fileSmallGraph->replot();
    if(graphAppendButton->isChecked())
    {
        ui->fileSmallGraph->xAxis->setLabel(actualNameMassive[graphAppendButton->objectName().toInt()]);
        if(graphAppendButton->isChecked()){
            for(int j = 0; j<devicesCount;++j){
                if(filedeviceChanger == j)
                {
                    ui->fileSmallGraph->yAxis->setLabel("Device "+QString::number(j));
                    for(int i=0; i <fileReadVector.size();++i)
                    {
                        if(fileReadVector[i].subscriberNumber == j)
                        {
                            emit graphsFileSignal(graphAppendButton,i,true);
                        }
                    }
                }
            }

            ui->fileSmallGraph->rescaleAxes();
            ui->fileSmallGraph->replot();
        }
        ui->fileSmallTrajectoryView->show();
    }
}


void guiCreator::showPics()
{
    QDir dir("flights");
    QFileInfoList dirContent = dir.entryInfoList(QStringList()
                                                 << "*.JPG");
    QRadioButton *cells[dirContent.size()];
    QLabel *picInfoCells[dirContent.size()];

    QRadioButton *cellsFile[dirContent.size()];
    QLabel *picInfoCellsFile[dirContent.size()];

    int x = 0;
    for(int i=0;i<=dirContent.size()-1;i++)
    {
        QFile file(dirContent[i].absoluteFilePath());//путь файла для записи
        QFileInfo fileinfo(file.fileName());
        QString filename(fileinfo.fileName());

        cellsFile[i] = new QRadioButton(ui->picButtonFilePlace);
        cellsFile[i]->setText(filename);
        cellsFile[i]->setCheckable(true);
        cellsFile[i]->setGeometry(QRect(0, 0, 300, 30));
        cellsFile[i]->move(0,x);
        cellsFile[i]->setCursor(QCursor(Qt::PointingHandCursor));
        cellsFile[i]->setObjectName(QString(filename));
        cellsFile[i]->setStyleSheet("QRadioButton{font-size:17px;font:bold; border: 1px solid "+blackColor+"; color: "+blackColor+"}\
                                    QRadioButton::hover{background-color: "+greyColor+"; color: "+blackColor+"}\
                                    QRadioButton::checked{background-color: "+blackColor+"; color: "+whiteColor+"}\
                                    QRadioButton::indicator{background-color:transparent}");
                                    connect(cellsFile[i],SIGNAL(clicked()), this, SLOT(getFilePic()));

        picInfoCellsFile[i] = new QLabel(ui->picButtonFilePlace);
        picInfoCellsFile[i]->setText(fileinfo.lastModified().toString("dd.MM.yy hh:mm"));
        picInfoCellsFile[i]->setGeometry(QRect(0, 0, 164, 30));
        picInfoCellsFile[i]->move(299,x);
        picInfoCellsFile[i]->setStyleSheet("QLabel{font-size:12px; font:bold; border: 1px solid "+blackColor+"; color: "+blackColor+";}");


        picInfoCells[i] = new QLabel(ui->picButtonPlace);
        picInfoCells[i]->setText(fileinfo.lastModified().toString("dd.MM.yy hh:mm"));
        picInfoCells[i]->setGeometry(QRect(0, 0, 164, 30));
        picInfoCells[i]->move(299,x);
        picInfoCells[i]->setStyleSheet("QLabel{font-size:12px; font:bold; border: 1px solid "+blackColor+"; color: "+blackColor+";}");

        cells[i] = new QRadioButton(ui->picButtonPlace);
        cells[i]->setText(filename);
        cells[i]->setCheckable(true);
        cells[i]->setGeometry(QRect(0, 0, 300, 30));
        cells[i]->move(0,x);
        cells[i]->setCursor(QCursor(Qt::PointingHandCursor));
        cells[i]->setObjectName(QString(filename));
        cells[i]->setStyleSheet("QRadioButton{font-size:17px;font:bold; border: 1px solid "+blackColor+"; color: "+blackColor+"}\
                                QRadioButton::hover{background-color: "+greyColor+"; color: "+blackColor+"}\
                                QRadioButton::checked{background-color: "+blackColor+"; color: "+whiteColor+"}\
                                QRadioButton::indicator{background-color:transparent}");
                                connect(cells[i],SIGNAL(clicked()), this, SLOT(getPic()));
                file.close();
        x+=29;
    }
    ui->scrollAreaPic->setWidget(ui->picButtonPlace);
    ui->picButtonPlace->resize(465,x+1);
    ui->scrollAreaFilePic->setWidget(ui->picButtonFilePlace);
    ui->picButtonFilePlace->resize(465,x+1);
}


void guiCreator::getFilePic(){
    QRadioButton *namecells = (QRadioButton*) sender();

    if(namecells->isChecked())
    {
        ui->fileBigPhoto->clear();
        ui->fileBigPhoto->show();
        ui->fileBigPhoto->setScaledContents(true);
        ui->fileBigPhoto->setPixmap(QPixmap("flights/"+namecells->objectName()));
        ui->scrollAreaFileButtons->hide();
        ui->fileBigTrajectory->hide();
        ui->bigMaxTrajectoryFile->hide();
        ui->bigMinTrajectoryFile->hide();
        ui->fileBigVideo->hide();
    }
}


void guiCreator::getPic(){
    QRadioButton *namecells = (QRadioButton*) sender();

    if(namecells->isChecked())
    {
        ui->telemetricBigPhoto->clear();
        ui->telemetricBigPhoto->show();
        ui->telemetricBigPhoto->setScaledContents(true);
        ui->telemetricBigPhoto->setPixmap(QPixmap("flights/"+namecells->objectName()));

        ui->scrollAreaButtons->hide();
        ui->telemetricBigTrajectory->hide();
        ui->bigMaxTrajectory->hide();
        ui->bigMinTrajectory->hide();
    }
}


void guiCreator::telemetricButtonsCells(QRadioButton* button[],QRadioButton* fileButton[],QPushButton* infoButton[],QPushButton* graphButton[],QPushButton* graphFileButton[])
{
    int x = 0;
    for(int i=0;i<actualTelemetricSize;i++)
    {
        button[i] = new QRadioButton(ui->telemetricButtonsCells);
        button[i]->setText(actualNameMassive[i]);
        button[i]->setCheckable(true);
        button[i]->setGeometry(QRect(0, 0, 305, 40));
        button[i]->move(0,x);
        button[i]->setCursor(QCursor(Qt::PointingHandCursor));

        connect(button[i],SIGNAL(clicked()), this, SLOT(realTelemetricButtonsAction()));
        button[i]->setStyleSheet("QRadioButton{font-size:18px;font:bold; border: 1px solid "+blackColor+"; color: "+blackColor+"}\
                                 QRadioButton::hover{background-color: "+greyColor+"; color: "+blackColor+"}\
                                 QRadioButton::checked{background-color: "+blackColor+"; color: "+whiteColor+"}\
                                 QRadioButton::indicator{background-color:transparent}");

        telemetricInformation[i] = new QLabel(ui->telemetricButtonsCells);
        telemetricInformation[i]->setGeometry(QRect(304, 0, 294, 40));
        telemetricInformation[i]->move(304,x);
        telemetricInformation[i]->setStyleSheet("QLabel{font-size:18px; font:bold; border: 1px solid "+blackColor+"; color: "+blackColor+"}");

        fileButton[i] = new QRadioButton(ui->fileButtonsCells);
        fileButton[i]->setText(actualNameMassive[i]);
        fileButton[i]->setCheckable(true);
        fileButton[i]->setGeometry(QRect(0, 0, 558, 40));
        fileButton[i]->move(0,x);
        fileButton[i]->setCursor(QCursor(Qt::PointingHandCursor));
        fileButton[i]->setObjectName(QString::number(i));
        connect(fileButton[i],SIGNAL(clicked()), this, SLOT(fileTelemetricButtonsAction()));
        fileButton[i]->setStyleSheet("QRadioButton{font-size:17px;font:bold; border: 1px solid "+blackColor+"; color: "+blackColor+"}\
                                     QRadioButton::hover{background-color: "+greyColor+"; color: "+blackColor+"}\
                                     QRadioButton::checked{background-color: "+blackColor+"; color: "+whiteColor+"}\
                                     QRadioButton::indicator{background-color:transparent}");



                                     infoButton[i] = new QPushButton(ui->telemetricButtonsCells);
                infoButton[i]->setText("+");
        infoButton[i]->setCheckable(true);
        infoButton[i]->setGeometry(QRect(517, 0, 41, 40));
        infoButton[i]->move(517,x);
        infoButton[i]->setCursor(QCursor(Qt::PointingHandCursor));
        connect(infoButton[i],SIGNAL(clicked()), this, SLOT(telemetricInfoMove()));

        infoButton[i]->setStyleSheet("QPushButton{font-size:28px;font:bold; border: 1px solid "+blackColor+"; color: "+blackColor+";background-color: "+whiteColor+";}\
                                     QPushButton::hover{background-color: "+blackColor+"; color: "+whiteColor+";}\
                                     QPushButton::checked{background-color: "+blackColor+"; color: "+whiteColor+";}");
                                     infoButton[i]->setObjectName(QString::number(i));

                graphButton[i] = new QPushButton(ui->telemetricButtonsCells);
        graphButton[i]->setCheckable(true);
        graphButton[i]->setGeometry(QRect(557, 0, 40, 40));
        graphButton[i]->move(557,x);
        graphButton[i]->setCursor(QCursor(Qt::PointingHandCursor));
        connect(graphButton[i],SIGNAL(clicked()), this, SLOT(graphMove()));
        graphButton[i]->setStyleSheet("QPushButton{font-size:17px;font:bold; border: 1px solid "+blackColor+"; color: "+blackColor+";border-image: url(:/pics/graph.svg);}\
                                      QPushButton::hover{background-color: "+blackColor+"; color: "+blackColor+";border-image: url(:/pics/graphWhite.svg);}\
                                      QPushButton::checked{background-color: "+blackColor+"; color: "+blackColor+";border-image: url(:/pics/graphWhite.svg);}");
                                      graphButton[i]->setObjectName(QString::number(i));



                graphFileButton[i] = new QPushButton(ui->fileButtonsCells);
        graphFileButton[i]->setCheckable(true);
        graphFileButton[i]->setGeometry(QRect(558, 0, 40, 40));
        graphFileButton[i]->move(558,x);
        graphFileButton[i]->setCursor(QCursor(Qt::PointingHandCursor));
        connect(graphFileButton[i],SIGNAL(clicked()), this, SLOT(graphFileMove()));

        graphFileButton[i]->setStyleSheet("QPushButton{font-size:17px;font:bold; border: 1px solid "+blackColor+"; color: "+blackColor+";border-image: url(:/pics/graph.svg);}\
                                      QPushButton::hover{background-color: "+blackColor+"; color: "+blackColor+";border-image: url(:/pics/graphWhite.svg);}\
                                      QPushButton::checked{background-color: "+blackColor+"; color: "+blackColor+";border-image: url(:/pics/graphWhite.svg);}");
                                          graphFileButton[i]->setObjectName(QString::number(i));
                x+=39;
    }
    ui->scrollAreaButtons->setWidget(ui->telemetricButtonsCells);
    ui->telemetricButtonsCells->resize(600,x+1);
    ui->scrollAreaButtons->setGeometry(623, 220, 670, 657);
    ui->scrollAreaFileButtons->setWidget(ui->fileButtonsCells);
    ui->fileButtonsCells->resize(600,x+1);
    ui->scrollAreaFileButtons->setGeometry(623, 220, 670, 657);
}


void guiCreator::telemetricInfoRemove(){
    QPushButton *removeButton = (QPushButton*) sender();
    infoTelemetric[removeButton->objectName().toInt()]->setChecked(0);
    smallTelemetricButton[removeButton->objectName().toInt()]->deleteLater();
    smallTelemetricInformation[removeButton->objectName().toInt()]->deleteLater();
    smallTelemetricButton[removeButton->objectName().toInt()]=0;
    smallTelemetricInformation[removeButton->objectName().toInt()]=0;
    telemetricInfoResize-=30;
    widgetForLayout->resize(440,telemetricInfoResize);
    if(ui->clearInfoSmall->isChecked()){

        for(int i=0;i<actualTelemetricSize;i++){
            if(smallTelemetricButton[i]){
                smallTelemetricButton[i]->deleteLater();
                smallTelemetricButton[i] = 0;
                smallTelemetricInformation[i]->deleteLater();
                smallTelemetricInformation[i]= 0;
                telemetricInfoResize-=30;
                infoTelemetric[i]->setChecked(0);
            }
            telemetricInfoResize = 10;
            widgetForLayout->resize(440,telemetricInfoResize);
            ui->clearInfoSmall->hide();
        }
    }
}


void guiCreator::telemetricInfoMove(){
    QPushButton *infoButton = (QPushButton*) sender();
    ui->clearInfoSmall->setCheckable(true);
    ui->clearInfoSmall->setChecked(false);
    ui->clearInfoSmall->show();
    ui->clearInfoSmall->setGeometry(QRect(511, 853, 40, 40));

    connect(ui->clearInfoSmall,SIGNAL(clicked()), this, SLOT(telemetricInfoRemove()));
    if(infoButton->isChecked())
    {
        if(!smallTelemetricButton[infoButton->objectName().toInt()])
        {
            smallTelemetricButton[infoButton->objectName().toInt()] = new QRadioButton(this);

            smallTelemetricButton[infoButton->objectName().toInt()]->setText(actualNameMassive[infoButton->objectName().toInt()]+"    ");
            smallTelemetricButton[infoButton->objectName().toInt()]->setCheckable(true);
            smallTelemetricButton[infoButton->objectName().toInt()]->setGeometry(QRect(0, 0, 300, 30));
            smallTelemetricButton[infoButton->objectName().toInt()]->setCursor(QCursor(Qt::PointingHandCursor));
            smallTelemetricButton[infoButton->objectName().toInt()]->setObjectName(infoButton->objectName());
            smallTelemetricButton[infoButton->objectName().toInt()]->setStyleSheet("QRadioButton{font-size:17px;font:bold; border: 1px solid "+blackColor+"; color: "+blackColor+"}\
                                                                                   QRadioButton::hover{background-color: "+greyColor+"; color: "+blackColor+"}\
                                                                                   QRadioButton::checked{background-color: "+blackColor+"; color: "+whiteColor+"}\
                                                                                   QRadioButton::indicator{background-color:transparent}");
            connect(smallTelemetricButton[infoButton->objectName().toInt()],SIGNAL(clicked()), this, SLOT(telemetricInfoRemove()));
            smallTelemetricInformation[infoButton->objectName().toInt()] = new QLabel(this);
            smallTelemetricInformation[infoButton->objectName().toInt()]->setText("no Data");
            smallTelemetricInformation[infoButton->objectName().toInt()]->setGeometry(QRect(0, 0, 300, 30));
            smallTelemetricInformation[infoButton->objectName().toInt()]->setStyleSheet("QLabel{font-size:12px; font:bold; border: 1px solid "+blackColor+"; color: "+blackColor+";}");
            smallTelemetricInformation[infoButton->objectName().toInt()]->setObjectName(infoButton->objectName());
            telemetricInfoResize+=30;
            formLayout->addRow(smallTelemetricButton[infoButton->objectName().toInt()],smallTelemetricInformation[infoButton->objectName().toInt()]);
            widgetForLayout->setLayout(formLayout);
            ui->telemetricInfoScrollArea->setWidget(widgetForLayout);
            ui->telemetricInfoScrollArea->setGeometry(28,566,482,315);
            widgetForLayout->resize(440,telemetricInfoResize);
        }

        else if(smallTelemetricButton[infoButton->objectName().toInt()])
        {
            smallTelemetricButton[infoButton->objectName().toInt()] = new QRadioButton(this);
            smallTelemetricButton[infoButton->objectName().toInt()]->setText(actualNameMassive[infoButton->objectName().toInt()]+"    ");
            smallTelemetricButton[infoButton->objectName().toInt()]->setCheckable(true);
            smallTelemetricButton[infoButton->objectName().toInt()]->setGeometry(QRect(0, 0, 300, 30));
            smallTelemetricButton[infoButton->objectName().toInt()]->setCursor(QCursor(Qt::PointingHandCursor));
            smallTelemetricButton[infoButton->objectName().toInt()]->setObjectName(infoButton->objectName());
            smallTelemetricButton[infoButton->objectName().toInt()]->setStyleSheet("QRadioButton{font-size:17px;font:bold;  color: "+blackColor+"}\
                                                                                   QRadioButton::hover{background-color: "+greyColor+"; color: "+blackColor+"; border: 1px solid "+blackColor+";}\
                                                                                   QRadioButton::checked{background-color: "+blackColor+"; color: "+whiteColor+"}\
                                                                                   QRadioButton::indicator{background-color:transparent}");

            connect(smallTelemetricButton[infoButton->objectName().toInt()],SIGNAL(clicked()), this, SLOT(telemetricInfoRemove()));
            smallTelemetricInformation[infoButton->objectName().toInt()] = new QLabel(this);
            smallTelemetricInformation[infoButton->objectName().toInt()]->setText("no Data");
            smallTelemetricInformation[infoButton->objectName().toInt()]->setGeometry(QRect(0, 0, 300, 30));
            smallTelemetricInformation[infoButton->objectName().toInt()]->setStyleSheet("QLabel{font-size:12px; font:bold; border: 1px solid "+blackColor+"; color: "+blackColor+";}");
            smallTelemetricInformation[infoButton->objectName().toInt()]->setObjectName(infoButton->objectName());
            formLayout->addRow(smallTelemetricButton[infoButton->objectName().toInt()],smallTelemetricInformation[infoButton->objectName().toInt()]);
        }

    }
    else if(!infoButton->isChecked())
    {
        if(smallTelemetricButton[infoButton->objectName().toInt()])
        {
            delete smallTelemetricButton[infoButton->objectName().toInt()];
            delete smallTelemetricInformation[infoButton->objectName().toInt()];
            smallTelemetricButton[infoButton->objectName().toInt()]=nullptr;
            smallTelemetricInformation[infoButton->objectName().toInt()]=nullptr;
            telemetricInfoResize-=30;
            widgetForLayout->resize(440,telemetricInfoResize);
        }
    }
};


QCustomPlot * smallPlots[actualTelemetricSize];


void guiCreator::realTelemetricButtonsAction()
{
    for (int i=0;i<actualTelemetricSize;i++)
    {
        if(cell[i]->isChecked())
        {
            realTelemetricMassive[i]=true;
            graphs.clearGraph(ui);
        }
        else realTelemetricMassive[i]=false;
    }
}


void guiCreator::on_fileShowGraphButton_clicked()
{
    ui->graphFileWidgetArea->setGeometry(309,90,1000,708);
    ui->graphFileWidgetArea->setGeometry(623, 220, 670, 657);
}


void guiCreator::on_telemetricGraphButton_clicked()
{
    ui->graphWidgetArea->setGeometry(309,90,1000,708);
    ui->graphWidgetArea->setGeometry(623, 220, 670, 657);
    ui->graphClearButton->show();
    ui->graphClearButton->setGeometry(1305, 520, 51, 51);
}


void guiCreator::warningSlot()
{
    graphs.warningInfo(ui,deviceChanger, telemetricMassiveActual);
}


void guiCreator::on_fileSent_clicked(){
    terminalsWindow.sendFile(0);
}


void guiCreator::newGraphSlot(){
    for(int i = 0; i <actualTelemetricSize;i++)
    {
        if(realTelemetricMassive[i])
        {
            ui->telemetricSmallGraph->xAxis->setLabel(actualNameMassive[i]);
            ui->telemetricGraphInfo->setNum(telemetricMassiveActual[i][deviceChanger]);
            ui->telemetricSmallGraph->graph(0)->addData(telemetricMassiveActual[6][deviceChanger], telemetricMassiveActual[i][deviceChanger]);
            ui->telemetricSmallGraph->graph(0)->rescaleValueAxis();
            ui->telemetricSmallGraph->xAxis->setRange(telemetricMassiveActual[6][deviceChanger], 8, Qt::AlignRight);
            ui->telemetricSmallGraph->yAxis->setLabel(QString::number(deviceChanger+1)+" Device");
            ui->telemetricSmallGraph->replot();
        }
    }
}


void guiCreator::trajectoryParamSlot(){
    graphs.trajectoryParam(deviceChanger, telemetricMassiveActual, ui);

}


void guiCreator::smallTelemetricButtonView(){
    for(int i = 0;i<actualTelemetricSize;i++)
    {
        if(smallTelemetricInformation[i])
        {
            smallTelemetricInformation[i]->setNum(telemetricMassiveActual[i][deviceChanger]);
        }
    }
}


void guiCreator::changeCoordinatesSlot()
{
    for(int i = 0; i<devicesCount; ++i){
        zMap.setNewCoordinates(telemetricMassiveActual[16][i],telemetricMassiveActual[17][i]);
    }

}

void guiCreator::on_graphClearButton_clicked()
{
    ui->graphClearButton->hide();
    for(int i=0;i<actualTelemetricSize;i++){
        if(smallPlots[i]){
            delete smallPlots[i];
            smallPlots[i]=nullptr;
            graphTelemetric[i]->setChecked(0);
        }
    }
}


void guiCreator::graphMove()//маленькие кнопки графиков
{
    QPushButton *graphAppendButton = (QPushButton*) sender();
    static int sizeg = 200;
    if(graphAppendButton->isChecked())
    {
        if(!smallPlots[graphAppendButton->objectName().toInt()])
        {
            smallPlots[graphAppendButton->objectName().toInt()] = new QCustomPlot();
            smallPlots[graphAppendButton->objectName().toInt()]->setObjectName(graphAppendButton->objectName());
            graphs.initializeGraph( smallPlots[graphAppendButton->objectName().toInt()]);
            smallPlots[graphAppendButton->objectName().toInt()]->xAxis->setLabel(actualNameMassive[graphAppendButton->objectName().toInt()]);
            graphVLayout->addWidget(smallPlots[graphAppendButton->objectName().toInt()]);
            ui->widgetForGraphLayout->resize(670,sizeg);
            ui->widgetForGraphLayout->setLayout(graphVLayout);
            sizeg+=200;
            ui->graphWidgetArea->setWidget(ui->widgetForGraphLayout);
            ui->graphWidgetArea->setGeometry(623, 220, 670, 657);
        }
    }
    else if(!graphAppendButton->isChecked())
    {
        if(ui->graphClearButton->isChecked()){
            if(smallPlots[graphAppendButton->objectName().toInt()])
            {
                delete smallPlots[graphAppendButton->objectName().toInt()];
                smallPlots[graphAppendButton->objectName().toInt()]=nullptr;
                sizeg-=200;
                ui->widgetForGraphLayout->resize(670,sizeg);
            }
        }
    }
}


void guiCreator::graphsSlot()
{
    for(int i=0;i<actualTelemetricSize;i++)
    {
        if(smallPlots[i])
        {
            graphsCreation(smallPlots[i]);
        }
    }
}


void guiCreator::graphFileMove()//маленькие кнопки графиков
{
    QPushButton *graphAppendButton = (QPushButton*) sender();
    static int sizeg = 200;
    if(graphAppendButton->isChecked())
    {
        if(!smallFilePlots[graphAppendButton->objectName().toInt()])
        {
            smallFilePlots[graphAppendButton->objectName().toInt()] = new QCustomPlot();
            smallFilePlots[graphAppendButton->objectName().toInt()]->setObjectName(graphAppendButton->objectName());
            graphs.initializeGraph( smallFilePlots[graphAppendButton->objectName().toInt()]);
            smallFilePlots[graphAppendButton->objectName().toInt()]->xAxis->setLabel(actualNameMassive[graphAppendButton->objectName().toInt()]);
            graphFileVLayout->addWidget(smallFilePlots[graphAppendButton->objectName().toInt()]);
            ui->widgetFileForGraphLayout->resize(670,sizeg);
            ui->widgetFileForGraphLayout->setLayout(graphFileVLayout);
            sizeg+=200;
            ui->graphFileWidgetArea->setWidget(ui->widgetFileForGraphLayout);
            ui->graphFileWidgetArea->setGeometry(623, 220, 670, 657);
            if(graphAppendButton->isChecked()){

            for(int j = 0; j<devicesCount;++j){
                if(filedeviceChanger == j)
                {
                    smallFilePlots[graphAppendButton->objectName().toInt()]->yAxis->setLabel("Device "+QString::number(j));
                    for(int i=0; i <fileReadVector.size();++i)
                    {
                        if(fileReadVector[i].subscriberNumber == j)
                        {
                            emit graphsFileSignal(graphAppendButton,i,false);
                        }
                    }
                }
            }
            smallFilePlots[graphAppendButton->objectName().toInt()]->rescaleAxes();
            smallFilePlots[graphAppendButton->objectName().toInt()]->replot();
            }
        }
    }
    else if(!graphAppendButton->isChecked())
    {
        if(smallFilePlots[graphAppendButton->objectName().toInt()])
        {
            delete smallFilePlots[graphAppendButton->objectName().toInt()];
            smallFilePlots[graphAppendButton->objectName().toInt()]=nullptr;
            sizeg-=200;
            ui->widgetFileForGraphLayout->resize(670,sizeg);
        }
    }
}


void guiCreator::graphsFileCreator(QPushButton* graphAppendButton,int i, bool smallGraph)
{
    graphFileShow(smallGraph, graphAppendButton->objectName().toInt(), smallFilePlots, fileReadVector, i);
}



