#ifndef NETWORKSERVICE_H
#define NETWORKSERVICE_H

#include <QObject>

#include<QMap>
#include <QNetworkReply>
#include<QVariantMap>

class QNetworkAccessManager;
class QNetworkReply;
class QSignalMapper;

class NetworkService;
class ISService;
class ISSObject;

class NetworkServiceWork : public QObject {
    Q_OBJECT

    Q_ENUMS(WorkType)

    Q_PROPERTY(WorkType type READ type CONSTANT)
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(float percent READ percent WRITE setPercent NOTIFY percentChanged)

    Q_PROPERTY(ISSObject* issobject READ issobject WRITE setIssobject NOTIFY issobjectChanged)

public:

    enum WorkType {
        Index,
        Thumbinal,
        Image,
        Other
    };

    NetworkServiceWork( WorkType type, QNetworkReply* reply, NetworkService *service );

    ~NetworkServiceWork();

    WorkType type() const;

    QNetworkReply *reply() const;

    float percent() const;

    ISSObject* issobject() const
    {
        return m_issobject;
    }

    int id() const
    {
        return m_id;
    }

public slots:
    void setPercent(float arg);

    void setIssobject(ISSObject* arg)
    {
        if (m_issobject != arg) {
            m_issobject = arg;
            emit issobjectChanged(arg);
        }
    }

    void setId(int arg)
    {
        if (m_id != arg) {
            m_id = arg;
            emit idChanged(arg);
        }
    }

signals:
    void percentChanged(float arg);

    void issobjectChanged(ISSObject* arg);

    void idChanged(int arg);

private slots:

    virtual void metaDataChanged();
    virtual void finished();
    virtual void error(QNetworkReply::NetworkError error);
//#ifndef QT_NO_SSL
//    void encrypted();
//    void sslErrors(const QList<QSslError> &errors);
//#endif

//    void uploadProgress(qint64 bytesSent, qint64 bytesTotal);
    virtual void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

private:

    WorkType m_type;
    QNetworkReply *m_reply;
    NetworkService *m_service;

    float m_percent;

    ISSObject* m_issobject;
    int m_id;
};


class NetworkService : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QObjectList works READ works WRITE setWorks NOTIFY worksChanged)

public:

    explicit NetworkService(QObject *parent = 0);
    
    Q_INVOKABLE QObject* get( QVariant const& obj );

    QNetworkAccessManager *getManager() const;
    void setManager(QNetworkAccessManager *value);

    ISService *getISService() const;
    void setISService(ISService *ISService);

    virtual void replyFinished( NetworkServiceWork * work );

    QObjectList works() const;

public slots:

    void setWorks(QObjectList arg)
    {
        if (m_works != arg) {
            m_works = arg;
            emit worksChanged(arg);
        }
    }

signals:
    void worksChanged(QObjectList arg);

    void objectReady( int request, QVariant data );

protected:

    int requestsCounter;

    int addReply( NetworkServiceWork* );

    QNetworkAccessManager* m_manager;

    ISService *m_ISService;

    QObjectList m_works;
};

#endif // NETWORKSERVICE_H
