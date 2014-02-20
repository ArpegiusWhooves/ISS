#ifndef ISSERVICE_H
#define ISSERVICE_H

#include <QObject>

#include <QQmlListProperty>

class QNetworkAccessManager;

class NetworkService;

class ISSObject;

class ISService : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QQmlListProperty<QObject> data READ data DESIGNABLE false)

    Q_CLASSINFO("DefaultProperty", "data")
public:


    explicit ISService(QObject *parent = 0);

    Q_INVOKABLE static QString className() {  return "ISService";  }
    
    QQmlListProperty<QObject> data()
    {
        return QQmlListProperty<QObject>(this, 0, ISService::data_append,
                                                 ISService::data_count,
                                                ISService::data_at,
                                                 ISService::data_clear );
    }

    Q_INVOKABLE ISSObject *newObject( QString id );

    void addObject( ISSObject* obj );

signals:
    


public slots:




private:

    QNetworkAccessManager *network_manager;

    QList< NetworkService* > network_services;

    QMap< long, ISSObject* > objects;

    static void data_append(QQmlListProperty<QObject> *property, QObject *value);
    static int data_count(QQmlListProperty<QObject> *property);
    static QObject *data_at(QQmlListProperty<QObject> *property, int index);
    static void data_clear(QQmlListProperty<QObject> *property);

};


#endif // ISSERVICE_H
