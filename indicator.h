#ifndef INDICATOR_H
#define INDICATOR_H

#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QMap>
#include <QTableWidget>

class indicator : public QWidget
{
    Q_OBJECT
public:
    indicator(QWidget *parent = 0);
    ~indicator();
    void setData(double r, double p) {
        m_roll = r;
        m_pitch = p;
        if( m_roll < -180 ) m_roll = -180;
        if( m_roll > 180  ) m_roll =  180;
        if( m_pitch < -90 ) m_pitch = -90;
        if( m_pitch > 90  ) m_pitch =  90;
        emit canvasReplot();
    }


    void setRoll(double val) {
        m_roll  = val;
        if( m_roll < -180 ) m_roll = -180;
        if( m_roll > 180  ) m_roll =  180;
        emit canvasReplot();
    }


    void setPitch(double val) {
        m_pitch = val;
        if( m_pitch < -90 ) m_pitch = -90;
        if( m_pitch > 90  ) m_pitch =  90;
        emit canvasReplot();
    }

    void keyUpdate(signed char roll,signed char pitch);

signals:
    void canvasReplot(void);

protected slots:
    void canvasReplot_slot(void);

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

protected:
    int     m_sizeMin, m_sizeMax;
    int     m_size, m_offset;
    double  m_roll;
    double  m_pitch;
};


#endif // INDICATOR_H
