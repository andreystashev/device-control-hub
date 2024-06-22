#ifndef MAPLIGHT_H
#define MAPLIGHT_H


#include <QBasicTimer>
#include <QWidget>
#include <QPushButton>




class mapCreator;

class LightMaps: public QWidget
{
    Q_OBJECT

public:
    LightMaps(QWidget *parent = 0);
    void setCenter(qreal lat, qreal lng);
    void vectAppend(double x,double y);
    void realCoordinatesTransfer(double x,double y);



public slots:
    void toggleNightMode();

protected:
    void activateZoom();
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *event);


private slots:
    void updateMap(const QRect &r);
    void click_button_plus();
    void click_button_minus();
    void click_button_arrow();

private:
    mapCreator *m_normalMap;
    mapCreator *m_largeMap;
    QPushButton *plus_button;
    QPushButton *minus_button;
    QPushButton *arrow_button;
    bool pressed;
    bool snapped;
    QPoint pressPos;
    QPoint dragPos;
    QBasicTimer tapTimer;
    bool zoomed;
    QPixmap zoomPixmap;
    QPixmap maskPixmap;
    bool invert;

};


#endif // MAPLIGHT_H
