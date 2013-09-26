#ifndef ISSERVICE_H
#define ISSERVICE_H

#include <QObject>

#include <QQmlListProperty>

class QNetworkAccessManager;

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


signals:
    


public slots:



private:

    static void data_append(QQmlListProperty<QObject> *property, QObject *value);
    static int data_count(QQmlListProperty<QObject> *property);
    static QObject *data_at(QQmlListProperty<QObject> *property, int index);
    static void data_clear(QQmlListProperty<QObject> *property);

    QNetworkAccessManager *network_manager;

};


#endif // ISSERVICE_H
