#ifndef NETWORKCREATOR_H
#define NETWORKCREATOR_H
#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QByteArray>
#include <QUdpSocket>
#include <QTcpServer>
#include <QThread>
#include <QTcpSocket>


class guiCreator;

class networkCreator : public QTcpServer
{
    Q_OBJECT
public:
    QString clientIP;
    int clientPort;
    QTcpSocket *socket = Q_NULLPTR;
    ~networkCreator();
    void newConnect();
    networkCreator(){};
    guiCreator* gui_network;

signals:
    void detachedSignal(QByteArray*);

    void alreadyRead();
    void arrayByteSend(QByteArray*);
    void arrayNewByteSend(QByteArray*,uint16_t);
    void socketArrayNewByteSend(QByteArray*,uint16_t);
    void socketArrayNewCommandSend(QTcpSocket *);

private slots:
    void readyRead();
    void disconnected();
    void readMessage();
    void socketReadMessage();

protected:
        void incomingConnection(qintptr handle);

private:
    QSet<QTcpSocket*> clients;
};

extern QVector<QByteArray> writtenVector;
extern QVector<QByteArray> writtenVectorNewMassives;
extern QVector<QByteArray> writtenVectorBDMassives;


class StreamerThread : public QThread
{
    Q_OBJECT

public:
    StreamerThread(QObject *parent);
    void run();
    QTcpSocket *socket;

private:
    QByteArray m_baImage;
    bool m_quit;

private slots:
    void slotQuit();

signals:
    void signalNouvelleImage(QByteArray baImage);

};


class wideSocket : public QUdpSocket
{
    Q_OBJECT
public:
    QString clientIP;
    int clientPort;
    QUdpSocket *socket = Q_NULLPTR;
    wideSocket(guiCreator*){};
    ~wideSocket();
    void newConnect();
    void newConnectSettingsBD();
    void newConnectVoiceHalper();
    guiCreator* wideGui_network;
    QString handleRequest(const QString &request);
    qreal getValueForQuestion(int questionNumber);

signals:
    void arrayWideByteSend(QByteArray*);
    void arrayWideByteSendSettingsBD(QByteArray*);

private slots:
    void disconnected();
    void readMessage();
    void readMessageSettingsBD();
    void readMessageVoiceHalper();

private:
    QSet<QUdpSocket*> wideClients;
};



#endif // NETWORKCREATOR_H
