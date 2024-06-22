#include <QTcpSocket>
#include <QVector>
#include <QDebug>
#include "messages.h"
#include "networkcreator.h"
#include <QDataStream>
#include <QBuffer>


QVector<QByteArray> writtenVector;
QVector<QByteArray> writtenVectorNewMassives;
QVector<QByteArray> writtenVectorBDMassives;


networkCreator::~networkCreator()
{
    delete socket;
}


void networkCreator::newConnect()//uart connection
{
    clientIP = "127.0.0.1";
    clientPort = 65500;
    if(socket == Q_NULLPTR) {
        socket = new QTcpSocket;
    }
    socket->connectToHost(clientIP,clientPort);
    connect(socket,SIGNAL(readyRead()),this,SLOT(readMessage()));
}


void networkCreator::readMessage() //uart reading
{
    static QByteArray headerArray;
    static QByteArray controlSumArray;
    static QByteArray dataArray;
    static QByteArray bigBuffer;
    static QByteArray vectorBuffer;
    QByteArray *pDataArray = &dataArray;
    bigBuffer.append(socket->readAll());
    int bigBufferSize = bigBuffer.size();

    for (int i = 0; i < bigBufferSize; i++)
    {
        if (bigBuffer.at(i) == 0x3A)
        {
            if (bigBufferSize >= i + 6)
            {
                headerArray = bigBuffer.mid(i, 6);
                vectorBuffer=headerArray;
                uint16_t length = (headerArray.at(5) << 8) | headerArray.at(4);
                if (bigBufferSize >= i + 6 + length + 2)
                {
                    bigBuffer.remove(0, i + 6);
                    dataArray = bigBuffer.mid(0, length);
                    vectorBuffer.append(dataArray);
                    uint16_t id = (dataArray.at(0) << 8) | dataArray.at(1);
                    emit arrayNewByteSend(pDataArray, id);
                    bigBuffer.remove(0, length);
                    controlSumArray = bigBuffer.mid(0, 2);
                    vectorBuffer.append(controlSumArray);
                    writtenVectorNewMassives.push_back(vectorBuffer);
                    vectorBuffer.clear();
                    bigBuffer.remove(0, 2);
                }
            }
        }
    }
}


void networkCreator::incomingConnection(qintptr socketfd)//socket connection
{
    QTcpSocket *client = new QTcpSocket(this);
    client->setSocketDescriptor(socketfd);
    clients.insert(client);
    connect(client, SIGNAL(readyRead()), this, SLOT(socketReadMessage()));
    connect(client, SIGNAL(disconnected()), this, SLOT(disconnected()));
}


void networkCreator::readyRead()//socket read
{
    static QByteArray array;
    QByteArray *pArray;
    QTcpSocket *client = (QTcpSocket*)sender();
    while(client->bytesAvailable()>0)
    {
        array = client->read(sizeof(ActualTelemetricMessage));
        pArray = &array;
        array.squeeze();
        writtenVector.push_back(array);
        emit detachedSignal(pArray);
    }
}


void networkCreator::socketReadMessage() // uart read
{
    static QByteArray headerArray;
    static QByteArray controlSumArray;
    static QByteArray dataArray;
    static QByteArray bigBuffer;
    static QByteArray vectorBuffer;
    QByteArray *pDataArray = &dataArray;
    QTcpSocket *client = (QTcpSocket*)sender();

    while(client->bytesAvailable()>0)
    {
            bigBuffer.append(client->readAll());
        qDebug()<<bigBuffer.toHex()<<"vectorBuffer";

    int bigBufferSize = bigBuffer.size();
        for (int i = bigBufferSize-1; i >= 0; --i)
        {
            if (bigBuffer.at(i) == 0x3A)
            {
                if (bigBufferSize >= i + 6)
                {
                    headerArray = bigBuffer.mid(i, 6);
                    vectorBuffer=headerArray;
                    uint16_t length = (headerArray.at(5) << 8) | headerArray.at(4);
                    if (bigBufferSize >= i + 6 + length + 2)
                    {
                        dataArray = bigBuffer.mid(i+6, length);
                        vectorBuffer.append(dataArray);
                        uint16_t id = (dataArray.at(0) << 8) | dataArray.at(1);
                        emit socketArrayNewByteSend(pDataArray, id);

                        controlSumArray = bigBuffer.mid(i+6+length, 2);
                        vectorBuffer.append(controlSumArray);
                        writtenVectorNewMassives.push_back(vectorBuffer);
                        vectorBuffer.clear();
                        bigBuffer.remove(i, 6+length+2);
                    }
                }
            }
        }
    }
}


void networkCreator::disconnected()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    qDebug() << "Client disconnected:" << client->peerAddress().toString();
    clients.remove(client);
}


StreamerThread::StreamerThread(QObject *)
{
    m_quit = 0;
}


void StreamerThread::run()
{
    socket = new QTcpSocket();
    socket->connectToHost("127.0.0.1", 9000);

    socket->write(new char[4]{1,2,3,4});
    QByteArray buffer;
    while(m_quit == 0)
    {
        if (socket->waitForReadyRead(3000))
        {
            buffer.append(socket->readAll());
            if ((unsigned char)buffer.right(2)[0] == 0xff && (unsigned char)buffer.right(2)[1] == 0xd9)
            {
                emit signalNouvelleImage(buffer);
                buffer.clear();
            }
        }
    }
}


void StreamerThread::slotQuit()
{
    m_quit = 1;
}


wideSocket::~wideSocket()
{
    delete socket;
}


void wideSocket::newConnect()//udp connection
{
    clientPort = 5000;
    if(socket == Q_NULLPTR) {
        socket = new QUdpSocket;
    }
    socket->bind(QHostAddress::Any,clientPort);
    connect(socket,SIGNAL(readyRead()),this,SLOT(readMessage()));
}


void wideSocket::newConnectSettingsBD()
{
    clientPort = 10121;
    if(socket == Q_NULLPTR) {
        socket = new QUdpSocket;
    }
}


void wideSocket::newConnectVoiceHalper(){

    clientPort = 10122;
    if(socket == Q_NULLPTR) {
        socket = new QUdpSocket;
    }
    socket->bind(QHostAddress::Any,clientPort);
    connect(socket,SIGNAL(readyRead()),this,SLOT(readMessageVoiceHalper()));
}


void wideSocket::readMessageVoiceHalper()
{
    while (socket->hasPendingDatagrams()) {
        QByteArray datagram;
        QHostAddress senderAddress;
        quint16 senderPort;
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size(),
                                &senderAddress, &senderPort);

        QString request = QString::fromUtf8(datagram);
        QString response = handleRequest(request);

        QByteArray responseData = response.toUtf8();
        socket->writeDatagram(responseData, senderAddress, senderPort);
    }
}


QString wideSocket::handleRequest(const QString &request)
{
    QStringList parts = request.split(' ');

    if (parts.length() == 2 && parts.at(0) == "6" && parts.at(1) == "2") {
        return "1 2 3";
    } else if (parts.length() == 3 && parts.at(0) == "4" && parts.at(1) == "123.456") {
        return QString("4 123.456 %1").arg(getValueForQuestion(4));
    } else {
        return "error";
    }
}


qreal wideSocket::getValueForQuestion(int questionNumber)
{
    // Здесь можно реализовать логику получения значения для заданного вопроса
    return questionNumber;
}


void wideSocket::readMessageSettingsBD()
{
    QHostAddress *address = new QHostAddress();

    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());
    socket->readDatagram(buffer.data(), buffer.size(), address);

    if(buffer.size() == 130 && buffer.mid(0, 2) == QByteArray::fromHex("F353"))
    {
        static QByteArray packetData;
        packetData.clear();
        packetData.resize(130);
        packetData.append(buffer);
        emit arrayWideByteSendSettingsBD(&packetData);
    }
}


void wideSocket::readMessage()
{
    QHostAddress *address = new QHostAddress();
    static QByteArray datagram;
    datagram.resize(sizeof(PacketReader));
    QByteArray *pDatagram;
    pDatagram = &datagram;
    socket->readDatagram(datagram.data(),datagram.size(),address);
    writtenVectorBDMassives.push_back(datagram);
    emit arrayWideByteSend(pDatagram);
}


void wideSocket::disconnected()
{
    QUdpSocket *client = (QUdpSocket*)sender();
    wideClients.remove(client);
}



