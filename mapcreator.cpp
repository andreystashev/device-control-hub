#include "mapcreator.h"

#include <math.h>
#include <QtWidgets>
#include <QtNetwork>
#include <QPointer>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

uint qHash(const QPoint& p)
{
    return p.x() * 17 ^ p.y();
}

const int tdim = 256;


QPointF tileForCoordinate(qreal lat, qreal lng, int zoom)
{
    qreal zn = static_cast<qreal>(1 << zoom);
    qreal tx = (lng + 180.0) / 360.0;
    qreal ty = (1.0 - log(tan(lat * M_PI / 180.0) +
                          1.0 / cos(lat * M_PI / 180.0)) / M_PI) / 2.0;
    return QPointF(tx * zn, ty * zn);
}

qreal longitudeFromTile(qreal tx, int zoom)
{
    qreal zn = static_cast<qreal>(1 << zoom);
    qreal lat = tx / zn * 360.0 - 180.0;
    return lat;
}

qreal latitudeFromTile(qreal ty, int zoom)
{
    qreal zn = static_cast<qreal>(1 << zoom);
    qreal n = M_PI - 2 * M_PI * ty / zn;
    qreal lng = 180.0 / M_PI * atan(0.5 * (exp(n) - exp(-n)));
    return lng;
}


mapCreator::mapCreator(QObject *parent)
    : QObject(parent), width(400), height(300), //zoom(5),
         latitude(44.5588), longitude(46.6731)
{
    m_emptyTile = QPixmap(tdim, tdim);
    m_emptyTile.fill(Qt::lightGray);

    QNetworkDiskCache *cache = new QNetworkDiskCache;
    cache->setCacheDirectory(QStandardPaths::writableLocation(QStandardPaths::CacheLocation));
    m_manager.setCache(cache);
    connect(&m_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(handleNetworkData(QNetworkReply*)));

    latitudeDevice[0] = 44.5588;
    longitudeDevice[0]= 46.6731;
    start_lat = 44.5588;
    start_lon = 46.6731;
}


void mapCreator::invalidate()
{
    if (width <= 0 || height <= 0)
        return;

    QPointF ct = tileForCoordinate(latitude, longitude, zoom);
    qreal tx = ct.x();
    qreal ty = ct.y();

    int xp = width / 2 - (tx - floor(tx)) * tdim;
    int yp = height / 2 - (ty - floor(ty)) * tdim;

    int xa = (xp + tdim - 1) / tdim;
    int ya = (yp + tdim - 1) / tdim;
    int xs = static_cast<int>(tx) - xa;
    int ys = static_cast<int>(ty) - ya;

    m_offset = QPoint(xp - xa * tdim, yp - ya * tdim);

    int xe = static_cast<int>(tx) + (width - xp - 1) / tdim;
    int ye = static_cast<int>(ty) + (height - yp - 1) / tdim;

    m_tilesRect = QRect(xs, ys, xe - xs + 1, ye - ys + 1);

    if (m_url.isEmpty())
        download();

    emit updated(QRect(0, 0, width, height));
}

void mapCreator::render(QPainter *p, const QRect &rect)
{
    int mx = 0, my = 0;
    for(int i = 0; i<devicesCount; ++i){
         qreal latdiff, lngdiff;
         QPointF center = tileForCoordinate(latitudeDevice[i], longitudeDevice[i], zoom);
         int cx = qFloor(center.x());
         int cy = qFloor(center.y());

        for (int x = 0; x <= m_tilesRect.width(); ++x)
            for (int y = 0; y <= m_tilesRect.height(); ++y) {
                QPoint tp(x + m_tilesRect.left(), y + m_tilesRect.top());
                QRect box = tileRect(tp);

                if (tp.x() == cx && tp.y() == cy) {
                mx = box.x();
                my = box.y();
                latdiff = qAbs(tp.x() - center.x());
                lngdiff = qAbs(tp.y() - center.y());
                }

                if (rect.intersects(box)) {
                    if (m_tilePixmaps.contains(tp))
                        p->drawPixmap(box, m_tilePixmaps.value(tp));
                    else
                        p->drawPixmap(box, m_emptyTile);
                }
            }
        QPixmap pixminus(":pics/pointRed.svg");
        QPainter painter(&pixminus);
        painter.setPen(Qt::white);
        painter.setFont(QFont("Arial", 45));
        painter.drawText(pixminus.rect(), Qt::AlignCenter, "1");
        painter.end();
        p->drawPixmap((mx+(latdiff*256.0)-40), (my+(lngdiff*256.0)-40),16,16, pixminus);
        p->setPen(QPen(Qt::black, 3, Qt::DashLine, Qt::FlatCap));

        invalidate();
    }
}


void mapCreator::pan(const QPoint &delta)
{
    QPointF dx = QPointF(delta) / qreal(tdim);
    QPointF center = tileForCoordinate(latitude, longitude, zoom) - dx;
    latitude = latitudeFromTile(center.y(), zoom);
    longitude = longitudeFromTile(center.x(), zoom);
    invalidate();
}


void mapCreator::handleNetworkData(QNetworkReply *reply)
{
    QImage img;
    QPoint tp = reply->request().attribute(QNetworkRequest::User).toPoint();
    QUrl url = reply->url();
    if (!reply->error())
        if (!img.load(reply, 0))
            img = QImage();
    reply->deleteLater();
    m_tilePixmaps[tp] = QPixmap::fromImage(img);
    if (img.isNull())
        m_tilePixmaps[tp] = m_emptyTile;
    emit updated(tileRect(tp));

    QRect bound = m_tilesRect.adjusted(-2, -2, 2, 2);
    foreach(QPoint tp, m_tilePixmaps.keys())
    if (!bound.contains(tp))
        m_tilePixmaps.remove(tp);
    download();
}


void mapCreator::download()
{
    QPoint grab(0, 0);
    for (int x = 0; x <= m_tilesRect.width(); ++x)
        for (int y = 0; y <= m_tilesRect.height(); ++y) {
            QPoint tp = m_tilesRect.topLeft() + QPoint(x, y);
            if (!m_tilePixmaps.contains(tp)) {
                grab = tp;
                break;
            }
        }
    if (grab == QPoint(0, 0)) {
        m_url = QUrl();
        return;
    }

    QString path = "file:./Tiles/%1/%2/%3.png";

    m_url = QUrl(path.arg(zoom).arg(grab.x()).arg(grab.y()));
    QNetworkRequest request;
    request.setUrl(m_url);
    request.setRawHeader("User-Agent", "The Qt Company (Qt) Graphics Dojo 1.0");
    request.setAttribute(QNetworkRequest::User, QVariant(grab));
    m_manager.get(request);
}


QRect mapCreator::tileRect(const QPoint &tp)
{
    QPoint t = tp - m_tilesRect.topLeft();
    int x = t.x() * tdim + m_offset.x();
    int y = t.y() * tdim + m_offset.y();
    return QRect(x, y, tdim, tdim);
}
