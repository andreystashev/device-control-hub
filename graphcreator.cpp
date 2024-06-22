#include "graphcreator.h"
#include <QDebug>
#include "playercreator.h"

void graphCreator::initializeGraph(QCustomPlot* plot){
    QFont font;
    font.setPointSize(17);
    font.setItalic(true);
    font.setBold(true);
    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%s");

    plot->addGraph();
    plot->graph(0)->setPen(QColor("red"));
    plot->setBackground(QBrush(QColor("white")));


    plot->graph(0)->setAntialiasedFill(true);
    plot->xAxis->setTicker(timeTicker);
    plot->axisRect()->setupFullAxesBox();
    plot->xAxis->setTickLabelFont(QFont(QFont().family(),10));
    plot->yAxis->setTickLabelFont(QFont(QFont().family(),10));
    plot->xAxis2->setTicks(false);
    plot->yAxis2->setTicks(false);
    plot->xAxis2->setTickLabels(false);
    plot->yAxis2->setTickLabels(false);
    if(Qt::Key_F11 > 0) {
    plot->setInteractions(QCP:: iRangeDrag | QCP:: iRangeZoom |QCP:: iSelectAxes | QCP:: iSelectLegend | QCP::iSelectPlottables |QCP::iMultiSelect |QCP::iSelectItems);
    plot->axisRect()->insetLayout()->setInsetAlignment(0 ,Qt :: AlignRight | Qt::AlignBottom);
    }
}


void graphCreator::clearGraph(Ui::guiUI* ui){
    ui->telemetricSmallGraph->graph(0)->data()->clear();
    ui->telemetricSmallGraph->rescaleAxes();
    ui->telemetricSmallGraph->graph(0)->rescaleValueAxis();
    ui->telemetricSmallGraph->replot();
}


void graphCreator::maxGraph(Ui::guiUI* ui){
    ui->telemetricBackgroundBig->show();
    ui->telemetricBackground->hide();
    ui->fileBackground->hide();
    ui->fileBackgroundBig->show();
    ui->fileShowGraphButton->hide();
    ui->fileBigGraph->hide();


    ui->graphWidgetArea->setGeometry(309,90,1319,908);
    ui->graphFileWidgetArea->setGeometry(309,90,1319,908);


    ui->layoutMap_3->setGeometry(QRect(309,90,1319,908));


    ui->telemetricGraphButton->hide();

    ui->telemetricBigPhoto->setGeometry(309,90,1319,908);
    ui->telemetricBigTrajectory->setGeometry(309,90,1319,908);
    ui->plusButton->hide();
    ui->minusButton->show();
    ui->telemetricShowButton->hide();
    ui->telemetricShowPhoto->hide();
    ui->telemetricTrajectoryButton->hide();
    ui->telemetricSmallGraph->hide();
    ui->scrollAreaPic->hide();
    ui->telemetricHeightInfo->hide();
    ui->telemetricHeightLabel->hide();
    ui->telemetricSpeedInfo->hide();
    ui->telemetricSpeedLabel->hide();
    ui->telemetricErrorLabel->setGeometry(820,40,161,41);
    ui->telemetricErrorInfo->setGeometry(1000,40,71,41);
    ui->scrollAreaButtons->setGeometry(309,90,1319,908);

    ui->telemetricBackgroundBig->show();
    ui->fileBigPhoto->setGeometry(309,90,1319,908);
    ui->fileBigTrajectory->setGeometry(309,90,1319,908);
    ui->fileMaxButton->hide();
    ui->fileMinButton->show();
    ui->fileBackgroundBig->show();
    ui->fileSmallGraph->hide();
    ui->fileTelemetricShowButton->hide();
    ui->rightbottom->hide();
    ui->scrollAreaFilePic->hide();
    ui->fileShowTrajectoryButton->hide();
    ui->fileSmallTrajectoryView->hide();
    ui->scrollAreaFileButtons->setGeometry(309,90,1319,908);

    ui->telemetricInfoScrollArea->hide();
    ui->telemetricSmallTrajectoryView->hide();

    ui->bigMaxTrajectory->setGeometry(1655,520,61,31);
    ui->bigMinTrajectory->setGeometry(1655,550,61,31);
    ui->maxTrajectory->hide();
    ui->minTrajectory->hide();
    ui->clearInfoSmall->hide();


    ui->bigMaxTrajectoryFile->setGeometry(1655,520,61,31);
    ui->bigMinTrajectoryFile->setGeometry(1655,550,61,31);
    ui->maxTrajectoryFile->hide();
    ui->minTrajectoryFile->hide();
    ui->graphClearButton->setGeometry(1702, 520, 51, 51);
    ui->fileBigVideo->setGeometry(QRect(309,90,1319,908));
};
void graphCreator::minGraph(Ui::guiUI* ui){
    ui->telemetricBackgroundBig->hide();
    ui->telemetricBackground->show();
    ui->fileBackground->show();
    ui->fileBackgroundBig->hide();

    ui->telemetricGraphButton->show();
    ui->fileShowGraphButton->show();
    ui->layoutMap_3->setGeometry(QRect(623, 220, 670, 657));


    ui->graphWidgetArea->setGeometry(623, 220, 670, 657);
    ui->graphFileWidgetArea->setGeometry(623, 220, 670, 657);
    ui->fileBigVideo->setGeometry(QRect(623, 220, 670, 657));


    ui->telemetricBigPhoto->setGeometry(623, 220, 670, 657);
    ui->telemetricBigTrajectory->setGeometry(623, 220, 670, 657);
    ui->minusButton->hide();
    ui->plusButton->show();
    ui->telemetricShowButton->show();
    ui->telemetricShowPhoto->show();
    ui->telemetricTrajectoryButton->show();
    ui->telemetricSmallGraph->show();
    ui->scrollAreaPic->show();
    ui->telemetricHeightInfo->show();
    ui->telemetricHeightLabel->show();
    ui->telemetricSpeedInfo->show();
    ui->telemetricSpeedLabel->show();
    ui->telemetricErrorLabel->setGeometry(820,170,161,41);
    ui->telemetricErrorInfo->setGeometry(1000,170,71,41);

    ui->scrollAreaButtons->setGeometry(623, 220, 670, 657);
    ui->fileBigPhoto->setGeometry(623, 220, 670, 657);
    ui->fileBigTrajectory->setGeometry(623, 220, 670, 657);
    ui->fileMaxButton->show();
    ui->fileMinButton->hide();
    ui->fileSmallGraph->show();
    ui->fileShowTrajectoryButton->show();
    ui->fileBackgroundBig->hide();
    ui->fileTelemetricShowButton->show();
    ui->fileSmallGraph->show();
    ui->rightbottom->show();
    ui->scrollAreaFilePic->show();
    ui->fileShowTrajectoryButton->show();
    ui->fileSmallTrajectoryView->show();
    ui->scrollAreaFileButtons->setGeometry(623, 220, 670, 657);

     ui->telemetricInfoScrollArea->show();
     ui->telemetricSmallTrajectoryView->show();

     ui->bigMaxTrajectory->setGeometry(1295,520,61,31);
     ui->bigMinTrajectory->setGeometry(1295,550,61,31);
     ui->bigMaxTrajectoryFile->hide();
     ui->bigMinTrajectoryFile->hide();

     ui->bigMaxTrajectoryFile->setGeometry(1295,520,61,31);
     ui->bigMinTrajectoryFile->setGeometry(1295,550,61,31);
     ui->graphClearButton->setGeometry(1305, 520, 51, 51);

};

void graphCreator::getIP(Ui::guiUI* ui)
    {
    int x = 0;
    int boardCount = devicesCount;
    QLabel *ipString[boardCount];
    QTextEdit *ipStringField[boardCount];
    QLabel *boardString[boardCount];
    QTextEdit *boardStringField[boardCount];
    for(int i=0;i<=boardCount-1;i++)
    {
        boardStringField[i] = new QTextEdit(ui->ipPlace);
        boardStringField[i]->setGeometry(QRect(341, 23, 341, 29));
        boardStringField[i]->move(140,x+28);
        boardStringField[i]->setStyleSheet("QTextEdit{font-size:15px;font:bold; border: 1px solid "+blackColor+"; color: "+blackColor+"}\
                                            QTextEdit::hover{background-color: "+blackColor+"; color: "+whiteColor+"}");
        boardStringField[i]->setText(QString::number(i+1));

        ipStringField[i] = new QTextEdit(ui->ipPlace);
        ipStringField[i]->setGeometry(QRect(341, 23, 341, 29));
        ipStringField[i]->move(140,x);
        ipStringField[i]->setStyleSheet("QTextEdit{font-size:15px;font:bold; border: 1px solid "+blackColor+"; color: "+blackColor+"}\
                                         QTextEdit::hover{background-color: "+blackColor+"; color: "+whiteColor+"}");
        ipStringField[i]->setText("127.0.0.1");

        ipString[i] = new QLabel(ui->ipPlace);
        ipString[i]->setText("Device IP "+QString::number(i+1)+": ");
        ipString[i]->setGeometry(QRect(0, 0, 141, 29));
        ipString[i]->move(0,x);
        ipString[i]->setStyleSheet("QLabel{font-size:17px;font:bold; border: 1px solid "+blackColor+"; color: "+blackColor+"}\
                                    QLabel::hover{background-color: "+blackColor+"; color: "+whiteColor+"}");

        boardString[i] = new QLabel(ui->ipPlace);
        boardString[i]->setText("Device Number "+QString::number(i+1)+": ");
        boardString[i]->setGeometry(QRect(0, 0, 141, 29));
        boardString[i]->move(0,x+28);
        boardString[i]->setStyleSheet("QLabel{font-size:17px;font:bold; border: 1px solid "+blackColor+"; color: "+blackColor+"}\
                                       QLabel::hover{background-color: "+blackColor+"; color: "+whiteColor+"}");
        x+=68;
    }

    ui->scrollAreaIp->setWidget(ui->ipPlace);
    ui->ipPlace->resize(482,x+1);

}

void graphCreator::firstInitialize(Ui::guiUI *ui)
{
    graphCreator::initializeGraph(ui->telemetricSmallGraph);
    graphCreator::initializeGraph(ui->fileSmallGraph);
    graphCreator::getIP(ui);

    ui->minusButton->hide();
    ui->fileMinButton->hide();

    ui->clearInfoSmall->hide();

    ui->textEditPort_2->hide();

    ui->groundButton->hide();
    ui->showFile->hide();

    ui->fileBigTrajectory->setGeometry(QRect(623, 220, 670, 657));
    ui->fileBigPhoto->setGeometry(QRect(623, 220, 670, 657));

    ui->fileBigTrajectory->hide();
    ui->fileBigPhoto->hide();
    ui->telemetricSmallTrajectoryView->hide();
    ui->layoutMap_3->setGeometry(QRect(623, 220, 670, 657));
    ui->layoutMap_4->setGeometry(QRect(111, 111, 670, 657));

    ui->telemetricBigPhoto->setGeometry(QRect(623, 220, 670, 657));
    ui->telemetricBigTrajectory->setGeometry(QRect(623, 220, 670, 657));

    ui->telemetricBigPhoto->hide();
    ui->telemetricBigTrajectory->hide();
    ui->bigMaxTrajectory->hide();
    ui->bigMinTrajectory->hide();
    ui->graphWidgetArea->hide();
    ui->graphFileWidgetArea->hide();
    ui->graphClearButton->hide();
    ui->textEditPort_2->hide();
    ui->fileSmallTrajectoryView->hide();
    ui->stackedWidget->setCurrentIndex(0);

    ui->flightPortWriter->hide();
    ui->flightStartConnect->hide();
    ui->flightLabel->hide();
    ui->textEditPort_2->hide();
    ui->scrollAreaIp->hide();
    ui->scrollAreaIp->setGeometry(QRect(706, 220, 501, 657));
    ui->telemetricBackgroundBig->hide();
    ui->fileBackgroundBig->hide();
    ui->graphWidgetArea->setGeometry(623, 220, 670, 657);

    ui->indico->setFrameShape(QFrame::NoFrame);
    ui->indico_2->setFrameShape(QFrame::NoFrame);
    ui->indico_3->setFrameShape(QFrame::NoFrame);


    ui->heightLine->setFrameShape(QFrame::NoFrame);
    ui->speedLine->setFrameShape(QFrame::NoFrame);
    ui->heightLine_2->setFrameShape(QFrame::NoFrame);
    ui->speedLine_2->setFrameShape(QFrame::NoFrame);
    ui->heightLine_3->setFrameShape(QFrame::NoFrame);
    ui->speedLine_3->setFrameShape(QFrame::NoFrame);

    ui->fileBigVideo->setGeometry(QRect(623, 220, 670, 657));
    ui->fileBigVideo->hide();

    ui->bigMaxTrajectoryFile->hide();
    ui->bigMinTrajectoryFile->hide();
    ui->maxTrajectoryFile->hide();
    ui->minTrajectoryFile->hide();
    ui->fileSmallTrajectoryView->hide();
    ui->fileBigTrajectory->hide();
    ui->fileSmallTrajectoryView->hide();
    ui->picButtonFilePlace->hide();
}


void graphCreator::warningInfo(Ui::guiUI *ui,int deviceChanger,double telemetricMassiveActual[actualTelemetricSize][devicesCount]){

    int height = telemetricMassiveActual[18][deviceChanger];
    int speed = telemetricMassiveActual[15][deviceChanger];
    int roll = telemetricMassiveActual[9][deviceChanger];

    if(deviceChanger==0)
    {
        ui->telemetricHeightInfo->setNum(height);
        ui->telemetricSpeedInfo->setNum(speed);

        if(-60>=roll || roll>=60){
            ui->telemetricErrorInfo->show();
            ui->telemetricErrorLabel->show();
            ui->telemetricErrorLabel->setText("Roll");
            ui->telemetricErrorInfo->setNum(int(roll));
        }
        else if(speed>=200){
            ui->telemetricErrorInfo->show();
            ui->telemetricErrorLabel->show();
            ui->telemetricErrorLabel->setText("Speed");
            ui->telemetricErrorInfo->setNum(int(speed));
        }

        else{
            ui->telemetricErrorLabel->hide();
            ui->telemetricErrorInfo->hide();
        }
    }
    else if(deviceChanger==1)
    {
        ui->telemetricHeightInfo->setNum(height);
        ui->telemetricSpeedInfo->setNum(speed);

        if(-60>=roll || roll>=60){
            ui->telemetricErrorInfo->show();
            ui->telemetricErrorLabel->show();
            ui->telemetricErrorLabel->setText("Roll");
            ui->telemetricErrorInfo->setNum(int(roll));
        }
        else if(speed>=200){
            ui->telemetricErrorInfo->show();
            ui->telemetricErrorLabel->show();
            ui->telemetricErrorLabel->setText("Скорость");
            ui->telemetricErrorInfo->setNum(int(speed));
        }

        else{
            ui->telemetricErrorLabel->hide();
            ui->telemetricErrorInfo->hide();
        }

    }
    else if(deviceChanger==2)
    {
        ui->telemetricHeightInfo->setNum(height);
        ui->telemetricSpeedInfo->setNum(speed);

        if(-60>=roll || roll>=60){
            ui->telemetricErrorInfo->show();
            ui->telemetricErrorLabel->show();
            ui->telemetricErrorLabel->setText("Roll");
            ui->telemetricErrorInfo->setNum(int(roll));
        }
        else if(speed>=200){
            ui->telemetricErrorInfo->show();
            ui->telemetricErrorLabel->show();
            ui->telemetricErrorLabel->setText("Speed");
            ui->telemetricErrorInfo->setNum(int(speed));
        }

        else{
            ui->telemetricErrorLabel->hide();
            ui->telemetricErrorInfo->hide();
        }

    }

        ui->controlHeightInfo->setNum(telemetricMassiveActual[18][0]);
        ui->controlSpeedInfo->setNum(telemetricMassiveActual[15][0]);

        if(-60>=telemetricMassiveActual[9][0] || telemetricMassiveActual[9][0]>=60){
            ui->controlErrorInfo->show();
            ui->controlErrorLabel->show();
            ui->controlErrorLabel->setText("Roll");
            ui->controlErrorInfo->setNum(int(telemetricMassiveActual[9][0]));
        }
        else if(telemetricMassiveActual[15][0]>=200){

            ui->controlErrorInfo->show();
            ui->controlErrorLabel->show();
            ui->controlErrorLabel->setText("Speed");
            ui->controlErrorInfo->setNum(int(telemetricMassiveActual[15][0]));

        }

        else{
            ui->controlErrorInfo->hide();
            ui->controlErrorLabel->hide();
        }

        ui->controlHeightInfo_2->setNum(telemetricMassiveActual[18][1]);
        ui->controlSpeedInfo_2->setNum(telemetricMassiveActual[15][1]);

        if(-60>=telemetricMassiveActual[9][1] || telemetricMassiveActual[9][1]>=60){
            ui->controlErrorInfo_2->show();
            ui->controlErrorLabel_2->show();
            ui->controlErrorLabel_2->setText("Roll");
            ui->controlErrorInfo_2->setNum(int(telemetricMassiveActual[9][1]));
        }
        else if(telemetricMassiveActual[15][1]>=200){

            ui->controlErrorInfo_2->show();
            ui->controlErrorLabel_2->show();
            ui->controlErrorLabel_2->setText("Speed");
            ui->controlErrorInfo_2->setNum(int(telemetricMassiveActual[15][1]));

        }

        else{
            ui->controlErrorInfo_2->hide();
            ui->controlErrorLabel_2->hide();
        }

        ui->controlHeightInfo_3->setNum(telemetricMassiveActual[18][2]);
        ui->controlSpeedInfo_3->setNum(telemetricMassiveActual[15][2]);

        if(-60>=telemetricMassiveActual[9][2] || telemetricMassiveActual[9][2]>=60){
            ui->controlErrorInfo_3->show();
            ui->controlErrorLabel_3->show();
            ui->controlErrorLabel_3->setText("Roll");
            ui->controlErrorInfo_3->setNum(int(telemetricMassiveActual[9][2]));
        }
        else if(telemetricMassiveActual[15][2]>=200){

            ui->controlErrorInfo_3->show();
            ui->controlErrorLabel_3->show();
            ui->controlErrorLabel_3->setText("Speed");
            ui->controlErrorInfo_3->setNum(int(telemetricMassiveActual[15][2]));

        }
        else{
            ui->controlErrorInfo_3->hide();
            ui->controlErrorLabel_3->hide();
        }
}


QMatrix matrix;
void graphCreator::telemetricTrajectory(Ui::guiUI *ui)
{
    matrix.scale(1,1);
    sceneTest = new QGraphicsScene();
    ui->telemetricSmallTrajectoryView->setGeometry(1405,214,485,320);
    ui->telemetricSmallTrajectoryView->setScene(sceneTest);
    ui->telemetricSmallTrajectoryView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->telemetricSmallTrajectoryView->centerOn(0,0);
    ui->telemetricSmallTrajectoryView->setMatrix(matrix.rotate(-90));

    for(int i = 0; i<devicesCount; ++i){
        device_trajectory[i] = new FalCirc(sceneTest);
        device_trajectory[i]->setPen(QPen(Qt::darkBlue,5,Qt::SolidLine));
        sceneTest->addItem(device_trajectory[i]);
    }

    sceneTestFile = new QGraphicsScene();

}

FalCirc::FalCirc(QGraphicsScene* parent){
    main_widg = parent;
    setRect(0,0,10,10);
    setPos(0,0);
    setPen(QPen(Qt::red,3,Qt::SolidLine));
    t=0;
    R=100;
    m=0.5;
    h=10;
}

void FalCirc::trajectory(double x,double y){
    x1 = x;
    y1 = y;
    x0=x1;
    y0=y1;
    main_widg->addLine(x0,y0,x1,y1,QPen(QColor(255,102,0),2,Qt::SolidLine));
    this->setPos(x1,y1);
}


void graphCreator::trajectoryParam(int deviceChanger, double telemetricMassiveActual[actualTelemetricSize][devicesCount], Ui::guiUI *ui)
{
    for(int i = 0; i<devicesCount; ++i){
        double a = telemetricMassiveActual[16][i];
        double b = telemetricMassiveActual[17][i];
        double resultLat = (a- (int)a);
        double resultLon = (b- (int)b);
        device_trajectory[i]->trajectory((resultLat*10000),(resultLon*10000));

        if(deviceChanger==i)
        {
            ui->telemetricSmallTrajectoryView->centerOn((resultLat*10000),(resultLon*10000));
            ui->telemetricBigTrajectory->centerOn((resultLat*10000),(resultLon*10000));
        }
    }
}


void graphCreator::trajectoryAloneParam(double latitude, double longitude){


    double a = latitude;
    double b = longitude;

    double resultLat = (a- (int)a);
    double resultLon = (b- (int)b);

    device_file_trajectory->trajectory((resultLat*10000),(resultLon*10000));

}


void graphCreator::graphCreation(const double &param, const double &time, Ui::guiUI *ui)
{
    double key = time;
    static double lastPointKey = 0;
    if(key - lastPointKey > 0.002)
    {
        ui->telemetricSmallGraph->graph(0)->addData(key, param);
        lastPointKey = key;
    }
    ui->telemetricSmallGraph->graph(0)->rescaleValueAxis();
    ui->telemetricSmallGraph->xAxis->setRange(key, 8, Qt::AlignRight);
    ui->telemetricSmallGraph->replot();
    lastPointKey = key;
}












