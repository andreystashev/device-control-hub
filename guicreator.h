#ifndef GUICREATOR_H
#define GUICREATOR_H

#include <QWidget>
#include <QRadioButton>
#include <QtNetwork>
#include <QTcpSocket>
#include "messages.h"
#include "QPushButton"
#include "QFormLayout"
#include "QVBoxLayout"
#include "QWidget"
#include "QScrollArea"
#include "qcustomplot.h"
#include "QGraphicsScene"
#include "QGraphicsView"
#include "QGraphicsItem"
#include "QGraphicsEllipseItem"
#include "networkcreator.h"
#include "mapzoom.h"
#include "mapcreator.h"


namespace Ui {
class guiUI;
};

class fileCreator;

class guiCreator : public QWidget
{
    Q_OBJECT

public:
    explicit guiCreator(QWidget *parent = nullptr);
    ~guiCreator();

    fileCreator* fileObj;
    networkCreator* NetworkBServer[devicesCount];
    networkCreator* NetworkBServer2[devicesCount];

    wideSocket* wideSocketMassive;
    wideSocket* wideSocketSettingsVoiceHalper;

    mapCreator s;
    mapCreator s1;
    mapCreator s2;

    QPoint oldPoz;

    QLabel *deviceFirstMassiveButton[10];
    QLabel *deviceFirstMassiveResults[10];
    QLabel *deviceSecondMassiveButton[10];
    QLabel *deviceSecondMassiveResults[10];
    QLabel *deviceThirdMassiveButton[10];
    QLabel *deviceThirdMassiveResults[10];


    QLabel *systemFirstMassiveButton[10];
    QLabel *systemFirstMassiveResults[10];
    QLabel *systemSecondMassiveButton[10];
    QLabel *systemSecondMassiveResults[10];
    QLabel *systemThirdMassiveButton[10];
    QLabel *systemThirdMassiveResults[10];

    QCustomPlot * smallFilePlots[actualTelemetricSize];

    int telemetricInfoResize = 10;

    bool fileTelemetricMassive[actualTelemetricSize]={false};
    QVector<ActualTelemetricMessage> fileReadVector;
    ActualTelemetricMessage fileReadMessage;

    QRadioButton *filedevice[devicesCount];
    QRadioButton *massivedeviceButton[devicesCount];
    QRadioButton *device[devicesCount];

    ActualTelemetricMessage commonMessage;
    ActualTelemetricMessage *detachedMessage = &commonMessage;

    ActualUartMessage UcommonMessage;
    ActualUartMessage *UdetachedMessage = &UcommonMessage;

    PacketReader PacketReaderMessage;
    PacketReader *pPacketReaderMessage = &PacketReaderMessage;

    systemFirst systemFirst_Massive_obj;
    systemFirst *PsystemFirst_Massive_obj = &systemFirst_Massive_obj;

    float scX = 1;
    float scY = 1;
    float scXF = 1;
    float scYF = 1;

    bool realTelemetricMassive[actualTelemetricSize]={true,false};

    QRadioButton *cell[actualTelemetricSize];
    QRadioButton *fileCell[actualTelemetricSize];
    QLabel *telemetricInformation[actualTelemetricSize];
    QPushButton * infoTelemetric[actualTelemetricSize];
    QPushButton * graphTelemetric[actualTelemetricSize];
    QPushButton * graphFileTelemetric[actualTelemetricSize];
    networkCreator *deviceSocket[devicesCount];
    networkCreator *imitatorSocket[devicesCount];
    int deviceChanger = 0;
    int filedeviceChanger = 0;
    int deviceMassiveChanger = 0;
    double telemetricMassiveActual[actualTelemetricSize][devicesCount];
    QRadioButton *TargetButton[actualTelemetricSize];

    void telemetricButtonsCells(QRadioButton* button[],QRadioButton* fileButton[],QPushButton* infoButton[],QPushButton* graphButton[],QPushButton* graphFileButton[]);
    void fileTelemetricButtonsCells(QRadioButton* button[]);
    void graphWriter(QString name,double param, double time);
    void graphCreatorG(const double &param, const double &time);
    void showFiles();
    void loadFlightData(QString DataId);
    void startServer();
    void warningInfo(ActualTelemetricMessage * param);
    void showPics();
    void showdeviceButtons();
    void showFiledeviceButtons();
    void showMassiveButtons();

signals:
    void arraysignal(QByteArray);
    void destroy();
    void signalGraph(QString name,double param, double time);
    void graphsFileSignal(QPushButton*, int, bool);

public slots:
    void regime();
    void flight();
    void ground();
    void file();
    void telemetric();
    void reference();
    void remoteControl();
    void handConnect();
    void regimeChoice();
    void terminal();
    void testSpace();
    void chart();
    void chart2();
    void read();
    void fileTelemetricButtonsAction();
    void realTelemetricButtonsAction();
    void writeData();
    void increaseGraph();
    void decreaseGraph();
    void getNum();
    void getPic();
    void getFilePic();
    void updatePhoto();
    void telemetricInfoMove();
    void telemetricInfoRemove();
    void ServerTimeTelemetric();
    void graphMove();
    void graphFileMove();
    void on_minTrajectory_clicked();
    void on_maxTrajectory_clicked();
    void on_bigMinTrajectory_clicked();
    void on_bigMaxTrajectory_clicked();
    void on_minTrajectoryFile_clicked();
    void on_maxTrajectoryFile_clicked();
    void on_bigMinTrajectoryFile_clicked();
    void on_bigMaxTrajectoryFile_clicked();
    void smallTelemetricButtonView();
    void trajectoryParamSlot();
    void newGraphSlot();
    void warningSlot();
    void graphsSlot();
    void graphsCreation(QCustomPlot *);
    void graphsFileCreator(QPushButton *, int ,bool);
    void on_fileShowGraphButton_clicked();
    void on_telemetricGraphButton_clicked();
    void on_graphClearButton_clicked();
    void slotNouvelleImage(QByteArray baImage);
    void changeTerminalSettings();
    void showTerminalPortInfo(int idx);
    void checkTerminalCustomBaudRatePolicy(int idx);
    void checkTerminalCustomDevicePathPolicy(int idx);
    void openTerminalSerialPort();
    void closeTerminalSerialPort();
    void getdeviceMassiveButton();
    void on_fileSent_clicked();
    void changeCoordinatesSlot();
    void fillNewInformationSlot(QByteArray *,uint16_t);

private slots:
    void wideMassiveSlot(QByteArray*);
    void fillInformationSlot(QByteArray*);
    void startUart(char const []);
    void getdeviceButton();
    void getFiledeviceButton();
    void on_sendMessage_clicked();
    void on_photoButton_clicked();
    void on_returnPPMButton_clicked();
    void on_parachuteButton_clicked();
    void on_deadButton_clicked();
    void on_userLink_clicked();

private:
    MapZoom zMap;
    QGraphicsScene* scene;
    QGraphicsScene* sceneTest;
    QGraphicsScene* sceneEmptyTest;
    QTimer* anim_timer;
    QTimer* anim_timer2;
    Ui::guiUI *ui;
    QTimer timer_plot;
    QCustomPlot *graphicPlot;
    int server_status;
    QMap<int,QTcpSocket *> SClients;
    QCustomPlot *mPlot;
    QPointer<QCPGraph> mGraph1;
    QPointer<QCPGraph> mGraph2;
    QTimer mDataTimer;
    QTimer mDataTimerTrajectory;
    QTimer mDataTimerGraph;
    QTimer mWideDataTimer;
    QFormLayout *laylay;

protected:
    QLabel *smallTelemetricInformation[actualTelemetricSize];
    QRadioButton *smallTelemetricButton[actualTelemetricSize];
    QFormLayout *formLayout = new QFormLayout();
    QFormLayout *fileFormLayout = new QFormLayout();
    QWidget *fileWidgetForLayout = new QWidget();
    QScrollArea *fileLayoutScroll = new QScrollArea();
    QWidget *widgetForLayout = new QWidget();
    QScrollArea *telemetricLayoutScroll = new QScrollArea();
    QVBoxLayout *graphVLayout = new QVBoxLayout();
    QVBoxLayout *graphFileVLayout = new QVBoxLayout();
};


#endif // GUICREATOR_H

