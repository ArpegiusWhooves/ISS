#ifndef NETWORKSERVICE_H
#define NETWORKSERVICE_H

#include <QObject>

#include<QMap>
#include<QVariantMap>

class QNetworkAccessManager;
class QNetworkReply;
class QSignalMapper;

class NetworkService : public QObject
{
    Q_OBJECT
public:
    explicit NetworkService(QObject *parent = 0);
    
    Q_INVOKABLE QObject* get( QVariant const& obj );

    QNetworkAccessManager *getManager() const;
    void setManager(QNetworkAccessManager *value);

signals:
        void objectReady( int request, QVariantMap object );

public slots:

protected:

    int addReply( QNetworkReply* );

    QNetworkAccessManager* manager;

    QSignalMapper* replyMapper;
    QMap< int, QNetworkReply* > replies;
    int requestCount;
    
};

#endif // NETWORKSERVICE_H
