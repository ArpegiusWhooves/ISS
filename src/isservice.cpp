#include "isservice.h"

#include <functional>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "issobject.h"

#include <QDebug>

#include <QStandardPaths>

#include "networkservice.h"


ISService::ISService(QObject *parent) :
    QObject(parent),
    network_manager( new QNetworkAccessManager( this ) )
{

    qDebug() << "Config Dir:" << QStandardPaths::standardLocations(QStandardPaths::ConfigLocation);
    qDebug() << "Cache Dir:" << QStandardPaths::standardLocations(QStandardPaths::CacheLocation);
    qDebug() << "Data Dir:" << QStandardPaths::standardLocations(QStandardPaths::DataLocation);

}

ISSObject *ISService::newObject(QString id)
{
    return new ISSObject(id,this);
}

void ISService::addObject(ISSObject *obj)
{

}

void ISService::data_append(QQmlListProperty<QObject> *property, QObject *value)
{
    qDebug() << " data_append " << property << ", " << value;
    if( NetworkService* ns= qobject_cast<NetworkService*>(value) )
    {
        qDebug() << "   NetworkService registred ";
        static_cast<ISService*>(property->object)->network_services.append(ns);
        ns->setISService( static_cast<ISService*>(property->object) );
        ns->setManager( static_cast<ISService*>(property->object)->network_manager );
    }

}

int ISService::data_count(QQmlListProperty<QObject> *property)
{
    qDebug() << " data_count " << property << " return " << property->object->children().count();
    return property->object->children().count();
}

QObject *ISService::data_at(QQmlListProperty<QObject> *property, int index)
{
    qDebug() << " data_at " << property << ", " << index << " return " << property->object->children().at(index);
    return property->object->children().at(index);
}

void ISService::data_clear(QQmlListProperty<QObject> *property)
{
    qDebug() << " data_clear " << property;
}
