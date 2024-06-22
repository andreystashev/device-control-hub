#ifndef SOCKETLOADER_H
#define SOCKETLOADER_H

#include <QObject>
#include <QTcpServer>

QT_FORWARD_DECLARE_CLASS(QTcpSocket)
QT_FORWARD_DECLARE_CLASS(QLabel)

class SocketLoader : public QObject
{
    Q_OBJECT
public:
    explicit SocketLoader(
//            QLabel *imageLabel,
            QObject *parent = 0);
    ~SocketLoader();

protected Q_SLOTS:
    void slotConnection();
    void readImage();

private:
    QLabel *m_imageLabel;
    QTcpServer m_server;
    QTcpSocket *m_socket;
};

#endif // SOCKETLOADER_H
