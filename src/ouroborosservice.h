#ifndef E621SERVICE_H
#define E621SERVICE_H

#include "networkservice.h"

#include <QString>
#include <QVariantMap>
#include <QStringList>

class QNetworkReply;

class OuroborosService;

class OuroborosIndexWork: public NetworkServiceWork
{

    OuroborosIndexWork( WorkType type, QNetworkReply* reply, OuroborosService *service );
public:

};

class OuroborosService : public NetworkService
{
    Q_OBJECT

    Q_PROPERTY(QString domain READ domain WRITE setDomain NOTIFY domainChanged)

public:
    explicit OuroborosService(QObject *parent = 0);

//       int requestImageInfoByFileMD5( QString md5 );
//       int requestImageInfoById( QString id );
       Q_INVOKABLE int requestImageInfoByTags( QStringList tags, int beforeId = -1 );

       Q_INVOKABLE NetworkServiceWork* requestImageFile( ISSObject* object, QUrl url );

    QString domain() const
    {
        return m_domain;
    }

signals:

    void domainChanged(QString arg);

public slots:

void setDomain(QString arg)
{
    if (m_domain != arg) {
        m_domain = arg;
        emit domainChanged(arg);
    }
}

private slots:

    virtual void replyFinished( NetworkServiceWork * work );

private:

QString m_domain;
};

#endif // E621SERVICE_H

