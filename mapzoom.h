#ifndef MAPZOOM_H
#define MAPZOOM_H

#include "ui_guicreator.h"


class QNetworkSession;
class LightMaps;

class MapZoom : public QWidget
{
    Q_OBJECT

public:
    MapZoom(QWidget *parent = nullptr);
    void initMap(Ui::guiUI *ui);
    void setNewCoordinates(double lat,double lon);


private slots:
    void sessionOpened();
    void choosePlace();

private:
    LightMaps *map;
    LightMaps *map2;

    QNetworkSession *networkSession;
    QMenu *menu;
};


#endif // MAPZOOM_H
