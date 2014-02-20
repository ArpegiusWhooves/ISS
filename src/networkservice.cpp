#include "networkservice.h"

#include "issobject.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSignalMapper>
#include <QFile>

#include <QDebug>

NetworkService::NetworkService(QObject *parent):
    QObject(parent),
    requestsCounter(0),
    m_manager(0),
    m_ISService(0)
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
    return m_manager;
}

void NetworkService::setManager(QNetworkAccessManager *value)
{
    m_manager = value;
}

int NetworkService::addReply( NetworkServiceWork* w)
{
    w->setId(++requestsCounter);
    m_works.append(w);
    return requestsCounter;
}

void NetworkService::replyFinished(NetworkServiceWork * work)
{
    if( work->reply()->error() == QNetworkReply::NoError )
    switch(work->type())
    {
        case NetworkServiceWork::Image:
        {
            ISSObject* obj= work->issobject();
            if( !obj ) break;

            if( obj->filePath().length() == 0 ) break;
            QFile outputfile( obj->filePath() );
            if( ! outputfile.open( QFile::WriteOnly ) ) break;
            qint64 size= outputfile.write( work->reply()->readAll() );
            qDebug() << "File " << obj->filePath() << " writed " << size;
            obj->setFileReady(true);
        }
        break;
    }

    m_works.removeAll( work );

    work->deleteLater();
}

QObjectList NetworkService::works() const
{
    return m_works;
}

ISService *NetworkService::getISService() const
{
    return m_ISService;
}

void NetworkService::setISService(ISService *value)
{
    m_ISService = value;
}

NetworkServiceWork::NetworkServiceWork(NetworkServiceWork::WorkType type, QNetworkReply *reply, NetworkService *service):
    m_type(type), m_reply(reply), m_service( service  ), m_percent(0), m_issobject( 0 )
{
    connect( reply, &QNetworkReply::downloadProgress, this, &NetworkServiceWork::downloadProgress );
    connect( reply, &QNetworkReply::finished, this, &NetworkServiceWork::finished );
    connect( reply, (void(QNetworkReply::*)(QNetworkReply::NetworkError))&QNetworkReply::error, this, &NetworkServiceWork::error );
    connect( reply, &QNetworkReply::metaDataChanged, this, &NetworkServiceWork::metaDataChanged );
}

NetworkServiceWork::~NetworkServiceWork()
{
    if(reply()) reply()->deleteLater();
}

NetworkServiceWork::WorkType NetworkServiceWork::type() const
{
    return m_type;
}

QNetworkReply *NetworkServiceWork::reply() const
{
    return m_reply;
}

float NetworkServiceWork::percent() const
{
    return m_percent;
}

void NetworkServiceWork::setPercent(float arg)
{
    if (m_percent != arg) {
        m_percent = arg;
        emit percentChanged(arg);
    }
}

void NetworkServiceWork::metaDataChanged()
{
    qDebug() << "(NetworkServiceWork)("<< this << ")::metaDataChanged()";
}

void NetworkServiceWork::finished()
{
    qDebug() << "(NetworkServiceWork)("<< this << ")::finished()";
    m_service->replyFinished(this);
}

void NetworkServiceWork::error(QNetworkReply::NetworkError error)
{
    qDebug() << "(NetworkServiceWork)("<< this << ")::error(" << error << ")";
}

void NetworkServiceWork::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
//    qDebug() << "(NetworkServiceWork)("<< this << ")::downloadProgress(" << ;
    if( bytesTotal == 0 )
    {
        setPercent(0);
    }
    else
        setPercent((bytesReceived*100.0)/bytesTotal);
}
