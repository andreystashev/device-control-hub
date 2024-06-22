#include <QtCore>
#include <QtWidgets>
#include <QtNetwork>
#include <math.h>
#include "maplight.h"
#include "messages.h"
#include "maplight.h"
#include "mapcreator.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


#define HOLD_TIME 701


#define MAX_MAGNIFIER 229

LightMaps::LightMaps(QWidget *parent)
    : QWidget(parent), pressed(false), snapped(false), zoomed(false),
      invert(false)
{
    m_normalMap = new mapCreator(this);
    m_largeMap = new mapCreator(this);
    connect(m_normalMap, SIGNAL(updated(QRect)), SLOT(updateMap(QRect)));
    connect(m_largeMap, SIGNAL(updated(QRect)), SLOT(update()));

    QPixmap pixplus(":/icons/plus.png");
    QIcon ButtonPlus(pixplus);
    plus_button = new QPushButton(this);
    plus_button->setGeometry(QRect(QPoint(10,61), QSize(40,40)));
    plus_button->setIcon(ButtonPlus);
    plus_button->setIconSize(pixplus.rect().size());
    plus_button->setText("+");
    plus_button->setStyleSheet("QPushButton{font-size:28px;font:bold; border: 1px solid "+blackColor+"; color: "+blackColor+"}\
                                QPushButton::hover{background-color: "+blackColor+"; color: "+whiteColor+"}");

    connect(plus_button, SIGNAL(released()), this, SLOT(click_button_plus()));

    QPixmap pixminus(":/icons/minus.png");
    QIcon ButtonMinus(pixminus);
    minus_button = new QPushButton(this);
    minus_button->setGeometry(QRect(QPoint(10,100), QSize(40,40)));
    minus_button->setIcon(ButtonMinus);
    minus_button->setIconSize(pixplus.rect().size());

    minus_button->setText("-");
    minus_button->setStyleSheet("QPushButton{font-size:28px;font:bold; border: 1px solid "+blackColor+"; color: "+blackColor+"}\
                                QPushButton::hover{background-color: "+blackColor+"; color: "+whiteColor+"}");

    connect(minus_button, SIGNAL(released()), this, SLOT(click_button_minus()));

    QPixmap pixarrow(":/icons/arrow.png");
    QIcon ButtonArrow(pixarrow);
    arrow_button = new QPushButton(this);
    arrow_button->setGeometry(QRect(QPoint(10,10), QSize(90,40)));
    arrow_button->setIcon(ButtonArrow);
    arrow_button->setIconSize(pixplus.rect().size());
    arrow_button->setText("You here");
    arrow_button->setStyleSheet("QPushButton{font-size:16px;font:bold; border: 1px solid "+blackColor+"; color: "+blackColor+"}\
                                QPushButton::hover{background-color: "+blackColor+"; color: "+whiteColor+"}");

    connect(arrow_button, SIGNAL(released()), this, SLOT(click_button_arrow()));


}

void LightMaps::setCenter(qreal lat, qreal lng)
{
    m_normalMap->latitude = lat;
    m_normalMap->longitude = lng;
    m_normalMap->invalidate();
    m_largeMap->latitude = lat;
    m_largeMap->longitude = lng;
    m_largeMap->invalidate();
}

void LightMaps::toggleNightMode()
{
    invert = !invert;
    update();
}

void LightMaps::updateMap(const QRect &r)
{
    update(r);
}

void LightMaps::click_button_plus()
{
    m_normalMap->pan(QPoint(0, 0));
    m_normalMap->zoom+=1;
    m_normalMap->invalidate();//обновление карты
    m_largeMap->invalidate();//обновление карты
}

void LightMaps::click_button_minus()
{
    m_normalMap->pan(QPoint(0, 0));
    m_normalMap->zoom-=1;
    m_normalMap->invalidate();//обновление карты
    m_largeMap->invalidate();//обновление карты
}

void LightMaps::click_button_arrow()
{
    this->setCenter(m_normalMap->latitudeDevice[0], m_normalMap->longitudeDevice[0]);
}

void LightMaps::activateZoom()
{
    zoomed = true;
    tapTimer.stop();
    m_largeMap->zoom = m_normalMap->zoom + 1;
    m_largeMap->width = m_normalMap->width * 2;
    m_largeMap->height = m_normalMap->height * 2;
    m_largeMap->latitude = m_normalMap->latitude;
    m_largeMap->longitude = m_normalMap->longitude;
    m_largeMap->invalidate();
    update();
}

void LightMaps::resizeEvent(QResizeEvent *)
{
    m_normalMap->width = width();
    m_normalMap->height = height();
    m_normalMap->invalidate();
    m_largeMap->width = m_normalMap->width * 2;
    m_largeMap->height = m_normalMap->height * 2;
    m_largeMap->invalidate();
}
void LightMaps::vectAppend(double x,double y){
    m_normalMap->x.push_back(x);
    m_normalMap->y.push_back(y);

}
void LightMaps::realCoordinatesTransfer(double x,double y){
    for(int i = 0; i<devicesCount;++i){
        m_normalMap->latitudeDevice[i]=x;
        m_normalMap->longitudeDevice[i]=y;
    }

}

void LightMaps::paintEvent(QPaintEvent *event)
{

    QPainter p;
    p.begin(this);
    m_normalMap->render(&p, event->rect());
    p.setPen(QPen(Qt::black, 3, Qt::DashLine, Qt::FlatCap));

    p.end();

    if (zoomed) {
        int dim = qMin(width(), height());
        int magnifierSize = qMin(MAX_MAGNIFIER, dim * 2 / 3);
        int radius = magnifierSize / 2;
        int ring = radius - 15;
        QSize box = QSize(magnifierSize, magnifierSize);

        // reupdate our mask
        if (maskPixmap.size() != box) {
            maskPixmap = QPixmap(box);
            maskPixmap.fill(Qt::transparent);

            QRadialGradient g;
            g.setCenter(radius, radius);
            g.setFocalPoint(radius, radius);
            g.setRadius(radius);
//            g.setColorAt(1.0, QColor(255, 255, 255, 0));
//            g.setColorAt(0.5, QColor(128, 128, 128, 255));

            QPainter mask(&maskPixmap);
            mask.setRenderHint(QPainter::Antialiasing);
            mask.setCompositionMode(QPainter::CompositionMode_Source);
//            mask.setBrush(g);
            mask.setPen(Qt::NoPen);
            mask.drawRect(maskPixmap.rect());
            mask.setBrush(QColor(Qt::transparent));
            mask.drawEllipse(g.center(), ring, ring);
            mask.end();
        }

        QPoint center = dragPos - QPoint(0, radius);
        center = center + QPoint(0, radius / 2);
        QPoint corner = center - QPoint(radius, radius);

        QPoint xy = center * 2 - QPoint(radius, radius);

        // only set the dimension to the magnified portion
        if (zoomPixmap.size() != box) {
            zoomPixmap = QPixmap(box);
            zoomPixmap.fill(Qt::lightGray);
        }
        if (true) {
            QPainter p(&zoomPixmap);
            p.translate(-xy);
            m_largeMap->render(&p, QRect(xy, box));
            p.end();
        }

        QPainterPath clipPath;
        clipPath.addEllipse(center, ring, ring);

        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);
        p.setClipPath(clipPath);
        p.drawPixmap(corner, zoomPixmap);
        p.setClipping(false);
        p.drawPixmap(corner, maskPixmap);
        p.setPen(Qt::gray);
        p.drawPath(clipPath);
    }
    if (invert) {
        QPainter p(this);
        p.setCompositionMode(QPainter::CompositionMode_Difference);
        p.fillRect(event->rect(), Qt::white);
        p.end();
    }
}

void LightMaps::timerEvent(QTimerEvent *)
{
    if (!zoomed)
        activateZoom();
    update();
}

void LightMaps::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() != Qt::LeftButton)
        return;
    pressed = snapped = true;
    pressPos = dragPos = event->pos();
    tapTimer.stop();
    tapTimer.start(HOLD_TIME, this);
}

void LightMaps::mouseMoveEvent(QMouseEvent *event)
{
    if (!event->buttons())
        return;
    if (!zoomed) {
        if (!pressed || !snapped) {
            QPoint delta = event->pos() - pressPos;
            pressPos = event->pos();
            m_normalMap->pan(delta);
            return;
        } else {
            const int threshold = 10;
            QPoint delta = event->pos() - pressPos;
            if (snapped) {
                snapped &= delta.x() < threshold;
                snapped &= delta.y() < threshold;
                snapped &= delta.x() > -threshold;
                snapped &= delta.y() > -threshold;
            }
            if (!snapped)
                tapTimer.stop();
        }
    } else {
        dragPos = event->pos();
        update();
    }
}

void LightMaps::mouseReleaseEvent(QMouseEvent *)
{
    zoomed = false;
    update();
}

void LightMaps::keyPressEvent(QKeyEvent *event)
{

    if(event->key() == Qt::Key_F10)
    {
        m_normalMap->pan(QPoint(0, 0));
        m_normalMap->zoom+=1;
        m_normalMap->invalidate();//обновление карты
        m_largeMap->invalidate();//обновление карты
    }
    if(event->key() == Qt::Key_F11)
    {
        m_normalMap->pan(QPoint(0, 0));
        m_normalMap->zoom-=1;
        m_normalMap->invalidate();
        m_largeMap->invalidate();
    }

    if (!zoomed) {
        if (event->key() == Qt::Key_Left){
            m_normalMap->pan(QPoint(20, 0));
//            m_normalMap->zoom+=1;
        }

        if (event->key() == Qt::Key_Right)
            m_normalMap->pan(QPoint(-20, 0));
        if (event->key() == Qt::Key_Up)
            m_normalMap->pan(QPoint(0, 20));
        if (event->key() == Qt::Key_Down)
            m_normalMap->pan(QPoint(0, -20));
        if (event->key() == Qt::Key_Z || event->key() == Qt::Key_Select) {
            dragPos = QPoint(width() / 2, height() / 2);
//            activateZoom();

        }
    } else {
        if (event->key() == Qt::Key_Z || event->key() == Qt::Key_Select) {
            zoomed = false;
            update();
        }
        QPoint delta(0, 0);
        if (event->key() == Qt::Key_Left)
            delta = QPoint(-15, 0);
        if (event->key() == Qt::Key_Right)
            delta = QPoint(15, 0);
        if (event->key() == Qt::Key_Up)
            delta = QPoint(0, -15);
        if (event->key() == Qt::Key_Down)
            delta = QPoint(0, 15);
        if (delta != QPoint(0, 0)) {
            dragPos += delta;
            update();
        }
    }
}
