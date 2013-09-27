#include "isservice.h"

#include <functional>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QDebug>

#include "networkservice.h"


ISService::ISService(QObject *parent) :
    QObject(parent),
    network_manager( new QNetworkAccessManager( this ) )
{

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
