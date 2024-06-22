#include "playercreator.h"
#include "messages.h"


void playerCreator::newConnect(Ui::guiUI* ui)
{
    videoPlayerLabel = new QLabel(ui->fileBigVideo);
    videoSlider = new QSlider(ui->fileBigVideo);
    videoPlayButton = new QPushButton(ui->fileBigVideo);
    videoInfo = new QLabel(ui->fileBigVideo);
    videoFindButton = new QPushButton(ui->fileBigVideo);
    videoFindCadre = new QTextEdit(ui->fileBigVideo);
    videoLoop = new QCheckBox(ui->fileBigVideo);
    videoSpeed = new QSpinBox(ui->fileBigVideo);
    timer = new QTimer(this);
    smallWindow();

    videoSlider->setOrientation(Qt::Horizontal);
    connect(videoSlider, SIGNAL(sliderMoved(int)), this, SLOT(sliderSlot(int)));
    connect(videoPlayButton, SIGNAL(clicked()), this, SLOT(playVideoSlot()));
    connect(videoFindButton, SIGNAL(clicked()), this, SLOT(showCadreSlot()));
    connect(videoSpeed, SIGNAL(valueChanged(int)), this, SLOT(speedSlot(int)));
    connect(timer, SIGNAL(timeout()), this, SLOT(Tick()));

    videoPlayButton->setCheckable(true);
    videoPlayButton->setText("Start");
    videoFindButton->setText("Frame");
    videoSlider->setMouseTracking(true);
    videoSpeed->setMaximum(6);
    videoSpeed->setValue(1);
    videoLoop->setText("Repeat");

    videoFindButton->setStyleSheet("QPushButton{font-size:17px;font:bold; border: 1px solid "+blackColor+"; ; color: "+blackColor+"; }\
                                                     QPushButton::hover{background-color: "+greyColor+"}\
                                                     QPushButton::checked{background-color: "+blackColor+"; color: "+whiteColor+"}");
    videoPlayButton->setStyleSheet("QPushButton{font-size:17px;font:bold; border: 1px solid "+blackColor+"; ; color: "+blackColor+"; }\
                                               QPushButton::hover{background-color: "+greyColor+"}\
                                               QPushButton::checked{background-color: "+blackColor+"; color: "+whiteColor+"}");
    videoSpeed->setStyleSheet("QSpinBox{font-size:15px;font:bold; border: 1px solid "+blackColor+"; color: "+blackColor+"}\
                           QSpinBox::hover{background-color: "+greyColor+"}");
    videoLoop->setStyleSheet("QCheckBox{font-size:12px;font:bold; color: "+blackColor+"}\
                          QCheckBox::hover{background-color: "+greyColor+"}");
    videoFindCadre->setStyleSheet("QTextEdit{font-size:15px;font:bold; border: 1px solid "+blackColor+"; color: "+blackColor+"}\
                               QTextEdit::hover{background-color: "+greyColor+"}");
    videoInfo-> setStyleSheet("QLabel{font-size:12px;font:bold;  color: "+blackColor+"}");
}


void playerCreator::initializeStart()
{
    dir= "flights/"+folderName+deviceName;
    dirContent = dir.entryInfoList(QStringList()<< "*.jpeg");
    cadresCount = dirContent.size();
    Display(_imgIndex);
}


void playerCreator::smallWindow()
{
    videoPlayerLabel->setGeometry(QRect(0, 0, 670, 600));
    videoSlider->setGeometry(QRect(0, 600, 670, 20));
    videoPlayButton->setGeometry(QRect(1, 621, 80, 35));
    videoSpeed->setGeometry(QRect(100, 621, 60, 35));
    videoLoop->setGeometry(QRect(170, 621, 100, 35));
    videoFindCadre->setGeometry(QRect(280, 621, 109, 35));
    videoFindButton->setGeometry(QRect(390, 621, 80, 35));
    videoInfo->setGeometry(QRect(500, 621, 169, 35));
}


void playerCreator::bigWindow()
{
    videoPlayerLabel->setGeometry(QRect(0, 0, 1319, 820));
    videoSlider->setGeometry(QRect(0, 821, 1319, 40));
    videoPlayButton->setGeometry(QRect(1, 862, 80, 45));
    videoSpeed->setGeometry(QRect(200, 862, 60, 45));
    videoLoop->setGeometry(QRect(300, 862, 100, 45));
    videoFindCadre->setGeometry(QRect(880, 862, 109, 45));
    videoFindButton->setGeometry(QRect(990, 862, 80, 45));
    videoInfo->setGeometry(QRect(1100, 862, 169, 45));
}


void playerCreator::Display(int index)
{
    QString actualTime, totalTime;
    videoSlider->setMaximum(cadresCount);
    QPixmap img = QPixmap(dir.path()+"/"+ dirContent[index].fileName());
    videoPlayerLabel->setScaledContents(true);
    videoPlayerLabel->setPixmap(QPixmap(img).scaled(QSize(1280,720), Qt::KeepAspectRatio));
    videoInfo->setText("Frame "+QString::number(index)+" / "+QString::number(cadresCount));
}


void playerCreator::Tick()
{
    _imgIndex++;
    if (_imgIndex >= cadresCount)
    {
        if (videoLoop->isChecked() == false)
        {
            _imgIndex = 0;
            Stop();
            Display(_imgIndex);
        }
        else
        {
            _imgIndex = 1;
        }
    }
    Display(_imgIndex);
    videoSlider->setValue(_imgIndex);
}


void playerCreator::tickManager(int speed)
{
    if (timer->isActive())
        timer->stop();
    if (speed < 0 || _isPlaying == false)
        return;
    if (speed != 0)
    {
        timer->start(1000 / (24 * speed));
    }
}


void playerCreator::sliderSlot(int position)
{
    _imgIndex = position;
    Display(_imgIndex);
}


void playerCreator::playVideoSlot()
{
    if (!_isPlaying)
    {
        Play();
    }
else{
        Stop();
    }
}


void playerCreator::speedSlot(int arg1)
{
    _speed = arg1;
    tickManager(_speed);
}


void playerCreator::Play()
{
    _isPlaying = true;
    videoPlayButton->setText("Pause");
    if (!timer->isActive())
    {
        tickManager(_speed);
    }
}


void playerCreator::Stop()
{
_isPlaying = false;
videoPlayButton->setText("Start");
if (timer->isActive())
    {
        timer->stop();
    }
}


void playerCreator::showCadreSlot(){
    Stop();
    if(videoFindCadre->toPlainText().toInt()<=cadresCount)
    {
        Display(videoFindCadre->toPlainText().toInt());
        sliderSlot(videoFindCadre->toPlainText().toInt());
        videoSlider->setValue(videoFindCadre->toPlainText().toInt());
        videoPlayButton->setChecked(false);
    }
    else{
        Display(cadresCount);
        sliderSlot(cadresCount);
        videoSlider->setValue(cadresCount);
        videoPlayButton->setChecked(false);
    }
}
