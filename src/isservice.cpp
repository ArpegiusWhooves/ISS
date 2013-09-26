#include "isservice.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QDebug>

ISService::ISService(QObject *parent) :
    QObject(parent),
    network_manager( new QNetworkAccessManager( this ) )
{

}

void ISService::data_append(QQmlListProperty<QObject> *property, QObject *value)
{
    qDebug() << " data_append " << property << ", " << value;
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
