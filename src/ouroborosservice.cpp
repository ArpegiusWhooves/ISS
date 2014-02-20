#include "ouroborosservice.h"

#include "isservice.h"
#include "issobject.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QSignalMapper>

#include <QDebug>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

#include <QStandardPaths>
#include <QDir>

OuroborosService::OuroborosService(QObject *parent) :
    NetworkService(parent)
{

}

int OuroborosService::requestImageInfoByTags( QStringList tags, int beforeId )
{
    QString args;

    if( beforeId > 0 ) {
        args= QString("before_id=%d&").arg(beforeId);
    }

    args += "tags=";
    args += tags.join(" ");

    QString address( "https://" + m_domain + "/post/index.json?" );
    QNetworkRequest rq( QUrl( address + args ) );

    return addReply(
        new NetworkServiceWork (
               NetworkServiceWork::Index,
               m_manager->get(rq),
               this
                    ) );
}

NetworkServiceWork* OuroborosService::requestImageFile(ISSObject *object, QUrl url)
{
    QDir path("/storage/sdcard0/Pictures/"); //QStandardPaths::writableLocation( QStandardPaths::PicturesLocation );

    QString filepath= "./" + m_domain + "/" + object->author() + "/";

    if(!path.exists(filepath)) path.mkpath(filepath);

    if( path.cd(filepath) )
        qDebug() << "cd to " << path;

    object->setFilePath( path.filePath( url.fileName() ) );

    if( path.exists( url.fileName() ) ) {
        object->setFileReady(true);
        return 0;
    }

    QNetworkRequest rq( url );

    NetworkServiceWork* work = new NetworkServiceWork (
           NetworkServiceWork::Image,
           m_manager->get(rq),
           this
                );

    work->setIssobject(object);

    addReply( work );

    return work;
}

void OuroborosService::replyFinished(NetworkServiceWork *work)
{
    if( work->type() != NetworkServiceWork::Index )
    {
        NetworkService::replyFinished(work);
        return;
    }

    QNetworkReply *r= work->reply();
    if( r->error() == QNetworkReply::NoError )
    {
        QByteArray data= r->readAll();
        QJsonDocument doc= QJsonDocument::fromJson( data );

        if(doc.isArray())
        {
            QJsonArray arr= doc.array();
            QJsonValue obj;
            Q_FOREACH( obj, arr )
            {
                QJsonObject v= obj.toObject();
                emit objectReady( work->id(), v.toVariantMap() );
            }
        }
        else
        {
            QJsonObject v= doc.object();
            emit objectReady( work->id(), v.toVariantMap() );
        }
    }
    else
    {
        qDebug() << " REQUEST " << work->id() << " ERROR: " << r->error();
    }

}


OuroborosIndexWork::OuroborosIndexWork(NetworkServiceWork::WorkType type, QNetworkReply *reply, OuroborosService *service):
    NetworkServiceWork( type, reply, service ){

}
