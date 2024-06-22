#ifndef MAPCREATOR_H
#define MAPCREATOR_H

#include <QNetworkAccessManager>
#include <QPixmap>
#include <QUrl>
#include "messages.h"




class QNetworkReply;
class QPainter;

class mapCreator: public QObject
{
    Q_OBJECT

public:
    mapCreator(QObject *parent = nullptr);
    void invalidate();
    void render(QPainter *p, const QRect &rect);
    void pan(const QPoint &delta);

    int width;
    int height;
    int zoom = 1;
    qreal latitude = 44.5588;
    qreal longitude =  46.6731;

    qreal latitudeDevice[devicesCount];
    qreal longitudeDevice[devicesCount];

    qreal start_lat;
    qreal start_lon;

    QVector<double> x;
    QVector<double> y;

signals:
    void updated(const QRect &rect);

private slots:
    void handleNetworkData(QNetworkReply *reply);
    void download();

public:
    QRect tileRect(const QPoint &tp);

public:
    QPoint m_offset;
    QRect m_tilesRect;
    QPixmap m_emptyTile;
    QHash<QPoint, QPixmap> m_tilePixmaps;
    QNetworkAccessManager m_manager;
    QUrl m_url;
};


#endif // MAPCREATOR_H
