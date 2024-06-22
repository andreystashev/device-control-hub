#include "socketloader.h"
#include <QTcpSocket>
#include <QDataStream>
#include <QImage>
#include <QLabel>
#include <QDebug>

SocketLoader::SocketLoader(
//        QLabel *imageLabel,
        QObject *parent) :
    QObject(parent)
//  ,
//    m_imageLabel(imageLabel)
{
    m_server.listen(QHostAddress::LocalHost, 4242);
    connect(&m_server, &QTcpServer::newConnection, this, &SocketLoader::slotConnection);
    qDebug()<<"server";


}

SocketLoader::~SocketLoader()
{
    if (m_socket) {
        m_socket->close();
        m_socket->deleteLater();
    }
    m_server.close();
}

void SocketLoader::slotConnection()
{
    m_socket = m_server.nextPendingConnection();
    connect(m_socket, &QTcpSocket::readyRead, this, &SocketLoader::readImage);
}

void SocketLoader::readImage()
{
    QDataStream in(m_socket);
    QImage image;
    in >> image;

    m_imageLabel->setPixmap(QPixmap::fromImage(image));
}
