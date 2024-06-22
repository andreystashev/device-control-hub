#include <QtWidgets>
#include <QtNetwork>
#include "maplight.h"
#include "mapzoom.h"
#include "QMenu"

MapZoom::MapZoom(QWidget *parent)
    : QWidget(parent)
{

    map = new LightMaps(this);
    map2 = new LightMaps(this);
    map->setFocus();
    map2->setFocus();

    QAction *placeAction = new QAction(tr("&Place"), this);
    QAction *nightModeAction = new QAction(tr("Night Mode"), this);
    nightModeAction->setCheckable(true);
    nightModeAction->setChecked(false);
    connect(placeAction, SIGNAL(triggered()), SLOT(choosePlace()));
    connect(nightModeAction, SIGNAL(triggered()), map, SLOT(toggleNightMode()));

    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));

        networkSession->open();
    } else {
        networkSession = 0;
    }

    setWindowTitle(tr("Maps"));


}

void MapZoom::initMap(Ui::guiUI *ui){

    ui->layoutMap_3->addWidget(map);

}

void MapZoom::sessionOpened()
{
    QNetworkConfiguration config = networkSession->configuration();
    QString id;
    if (config.type() == QNetworkConfiguration::UserChoice) {
        id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
    }
    else {
        id = config.identifier();
    }

    QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
    settings.beginGroup(QLatin1String("QtNetwork"));
    settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
    settings.endGroup();
}

void MapZoom::choosePlace()
{
    map->setCenter(44.5588, 46.6731);//dagestan
    map2->setCenter(44.5588, 46.6731);//dagestan

}



void MapZoom::setNewCoordinates(double lat,double lon)
{
    map->vectAppend(lat,lon);
    map2->vectAppend(lat,lon);
    map->realCoordinatesTransfer(lat,lon);
    map2->realCoordinatesTransfer(lat,lon);
}
