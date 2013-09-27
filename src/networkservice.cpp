#include "networkservice.h"



#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSignalMapper>

#include <QDebug>

NetworkService::NetworkService(QObject *parent):
    QObject(parent),
    manager(0),
    replyMapper( new QSignalMapper( this )),
    requestCount(0)
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

int NetworkService::addReply(QNetworkReply * r)
{
    int i=requestCount++;
    replies[i]= r;
    replyMapper->setMapping( r, i );
    connect( r, SIGNAL(finished()), replyMapper, SLOT(map()) );
    return i;
}
