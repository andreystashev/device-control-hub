#ifndef GRAPHCREATOR_H
#define GRAPHCREATOR_H
#include "ui_guicreator.h"
#include "messages.h"


class FalCirc:public QGraphicsEllipseItem{
public:
    FalCirc(QGraphicsScene* parent);

    QGraphicsScene* main_widg;

    void trajectory(double x,double y);
private:
    double t;
    double x0,y0,x1,y1;
    double R;
    double m;
    double h;
};

class graphCreator
{
public:
    Ui::guiUI* ui;
    FalCirc* f;
    FalCirc* device_trajectory[devicesCount];
    FalCirc* device_file_trajectory;

    QGraphicsScene* scene;
    QGraphicsScene* sceneTest;
    QGraphicsScene* sceneEmptyTest;
    QGraphicsScene* sceneTestFile;
    QGraphicsScene* sceneTestMAP;

    void telemetricTrajectory(Ui::guiUI *ui);
    void initializeGraph(QCustomPlot* plot);
    void clearGraph(Ui::guiUI*);
    void getIP(Ui::guiUI*);
    void firstInitialize(Ui::guiUI*);
    void warningInfo(Ui::guiUI *ui,int deviceChanger, double telemetricMassiveActual[actualTelemetricSize][devicesCount]);
    void trajectoryParam(int deviceChanger,double telemetricMassiveActual[actualTelemetricSize][devicesCount], Ui::guiUI *ui);
    void trajectoryAloneParam(double latitude, double longitude);
    void graphCreation(const double &param, const double &time, Ui::guiUI *ui);
public slots:
    void maxGraph(Ui::guiUI*);
    void minGraph(Ui::guiUI*);
    void fileGraphsCreation(QPushButton* graphAppendButton,int i, bool smallGraph,QVector<ActualTelemetricMessage> fileReadVector,QCustomPlot * smallFilePlots[], Ui::guiUI *ui);

};


#endif // GRAPHCREATOR_H
