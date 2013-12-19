#ifndef E621SERVICE_H
#define E621SERVICE_H

#include "networkservice.h"

#include <QString>
#include <QVariantMap>
#include <QStringList>

class QNetworkReply;

class OuroborosService : public NetworkService
{
    Q_OBJECT

public:
    explicit OuroborosService(QObject *parent = 0);

//       int requestImageInfoByFileMD5( QString md5 );
//       int requestImageInfoById( QString id );
       Q_INVOKABLE int requestImageInfoByTags( QStringList tags, int beforeId = -1 );

signals:

    
public slots:
    
private slots:
    void replyFinish(int map);

private:

};

#endif // E621SERVICE_H

