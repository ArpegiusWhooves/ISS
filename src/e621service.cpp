#include "e621service.h"


#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QSignalMapper>

#include <QDebug>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

E621Service::E621Service(QObject *parent) :
    NetworkService(parent)
{
    connect(replyMapper, SIGNAL(mapped(int)),
                this, SLOT(replyFinish(int)));
}

int E621Service::requestImageInfoByTags( QStringList tags, int beforeId )
{
    QString args;

    if( beforeId > 0 ) {
        args= QString("before_id=%d&").arg(beforeId);
    }

    args += "tags=";
    args += tags.join(" ");

    QString address( "https://e621.net/post/index.json?" );
    QNetworkRequest rq( QUrl( address + args ) );

    return addReply( manager->get( rq ) );

}

void E621Service::replyFinish(int map)
{
    QNetworkReply *r= replies[map];
    if( r->error() == QNetworkReply::NoError )
    {
        QByteArray data= r->readAll();
        qDebug() << " data ready: " << data;
        QJsonDocument doc= QJsonDocument::fromJson( data );

        if(doc.isArray())
        {
            QJsonArray arr= doc.array();
            QJsonValue obj;
            Q_FOREACH( obj, arr )
            {
                QVariant v= obj.toVariant();
                emit objectReady( map, v.toMap() );

            }
        }
        else
        {
            QVariant v= doc.toVariant();
            emit objectReady( map, v.toMap() );
        }
    }
    else
    {
        qDebug() << " REQUEST " << map << " ERROR: " << r->error();
    }



}
