#ifndef PLAYERCREATOR_H
#define PLAYERCREATOR_H
#include <QObject>
#include <QLabel>
#include <QSlider>
#include <QTextEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QCheckBox>
#include <QTimer>
#include <QDir>
#include <QFileInfoList>
#include "ui_guicreator.h"


class playerCreator: public QObject
{
    Q_OBJECT
public:
    explicit playerCreator(){};
    ~playerCreator()= default;
    QLabel *videoPlayerLabel;
    QSlider *videoSlider;
    QPushButton *videoPlayButton;
    QLabel *videoInfo;
    QTextEdit *videoFindCadre;
    QPushButton *videoFindButton;
    QCheckBox *videoLoop;
    QSpinBox *videoSpeed;
    QTimer *timer;
    int _speed = 1;
    bool _isPlaying = false;
    int _imgIndex = 0;
    int cadresCount = 0;
    QString folderName;
    QString deviceName = "";
    QDir dir;
    QFileInfoList dirContent;

    void newConnect(Ui::guiUI* ui);
    void smallWindow();
    void bigWindow();
    void initializeStart();

public slots:
    void Display(int index);
    void Tick();
    void Play();
    void Stop();
    void tickManager(int speed);
    void sliderSlot(int position);
    void playVideoSlot();
    void speedSlot(int arg1);
    void showCadreSlot();
};

#endif // PLAYERCREATOR_H

