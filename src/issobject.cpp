#include "issobject.h"

ISSObject::ISSObject( QObject *parent) :
    QObject(parent)
{

}
ISSObject::ISSObject( QString const& id, QObject *parent) :
    QObject(parent), m_id(id), m_fileReady(false)
{

}
