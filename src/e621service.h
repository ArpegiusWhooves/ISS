#ifndef E621SERVICE_H
#define E621SERVICE_H

#include "networkservice.h"
#include <QIODevice>

class E621Service : public NetworkService
{
    Q_OBJECT

public:
    explicit E621Service(QObject *parent = 0);

       QIODevice getObject( QString id );
       void getObject( QString hash );

       getImage( QVariant id );
    
signals:
    
       void objectReady( QVariantMap object );

public slots:
    
};

#endif // E621SERVICE_H
