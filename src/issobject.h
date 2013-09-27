#ifndef ISSOBJECT_H
#define ISSOBJECT_H

#include <QObject>



class ISSObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QObject* trueprent READ parent )
    Q_PROPERTY(SomeEnum someEnum READ someEnum WRITE setsomeEnum NOTIFY someEnumChanged)

    Q_ENUMS( SomeEnum )

public:
    explicit ISSObject(QObject *parent = 0);

    enum SomeEnum{
        SomeEnumValue,
        SomeOtherEnumValue,
        ThirdEnumValue
    };

    SomeEnum someEnum() const
    {
        return m_someEnum;
    }

signals:
    
    void someEnumChanged(SomeEnum arg);

public slots:

void setsomeEnum(SomeEnum arg)
{
    if (m_someEnum != arg) {
        m_someEnum = arg;
        emit someEnumChanged(arg);
    }
}

private:

    SomeEnum m_someEnum;
};

Q_DECLARE_METATYPE(ISSObject::SomeEnum)

#endif // ISSOBJECT_H
