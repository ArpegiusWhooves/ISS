#include "networkservice.h"



#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>


#include <QDebug>

NetworkService::NetworkService(QObject *parent) :
    QObject(parent)
{

}

QObject *NetworkService::get(QVariant const&  obj)
{
    qDebug() << "<< GET INFO: >>" ;
    qDebug()  << obj;
    qDebug() << "<< --------- >>" ;



    return this;
}

QNetworkAccessManager *NetworkService::getManager() const
{
    return manager;
}

void NetworkService::setManager(QNetworkAccessManager *value)
{
    manager = value;
}
