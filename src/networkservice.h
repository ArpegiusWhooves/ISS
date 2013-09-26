#ifndef NETWORKSERVICE_H
#define NETWORKSERVICE_H

#include <QObject>


class QNetworkAccessManager;

class NetworkService : public QObject
{
    Q_OBJECT
public:
    explicit NetworkService(QObject *parent = 0);
    
    Q_INVOKABLE QObject* get( QVariant const& obj );

    QNetworkAccessManager *getManager() const;
    void setManager(QNetworkAccessManager *value);

signals:
    
public slots:

private:
    QNetworkAccessManager* manager;
    
};

#endif // NETWORKSERVICE_H
