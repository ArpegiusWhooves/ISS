#ifndef ISSOBJECT_H
#define ISSOBJECT_H

#include <QObject>
#include <QStringList>



class ISSObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QObject* trueprent READ parent )
    Q_PROPERTY(SomeEnum someEnum READ someEnum WRITE setsomeEnum NOTIFY someEnumChanged)

    Q_ENUMS( SomeEnum )

    Q_PROPERTY(QString const& id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString author READ author WRITE setAuthor NOTIFY authorChanged)
    Q_PROPERTY(QString filePath READ filePath WRITE setFilePath NOTIFY filePathChanged)
    Q_PROPERTY(bool fileReady READ fileReady WRITE setFileReady NOTIFY fileReadyChanged)
    Q_PROPERTY(QStringList tags READ tags WRITE setTags NOTIFY tagsChanged)
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)

public:
    explicit ISSObject( QObject *parent = 0);
    explicit ISSObject( QString const& id ,QObject *parent = 0);

    enum SomeEnum{
        SomeEnumValue,
        SomeOtherEnumValue,
        ThirdEnumValue
    };

    SomeEnum someEnum() const
    {
        return m_someEnum;
    }

    QString id() const
    {
        return m_id;
    }

    QString filePath() const
    {
        return m_filePath;
    }

    bool fileReady() const
    {
        return m_fileReady;
    }

    QStringList tags() const
    {
        return m_tags;
    }

    int width() const
    {
        return m_width;
    }

    int height() const
    {
        return m_height;
    }

    QString author() const
    {
        return m_author;
    }

signals:
    
    void someEnumChanged(SomeEnum arg);

    void idChanged(QString arg);

    void filePathChanged(QString arg);

    void fileReadyChanged(bool arg);

    void tagsChanged(QStringList arg);

    void widthChanged(int arg);

    void heightChanged(int arg);

    void authorChanged(QString arg);

public slots:

void setsomeEnum(SomeEnum arg)
{
    if (m_someEnum != arg) {
        m_someEnum = arg;
        emit someEnumChanged(arg);
    }
}

void setId(QString arg)
{
    if (m_id != arg) {
        m_id = arg;
        emit idChanged(arg);
    }
}

void setFilePath(QString arg)
{
    if (m_filePath != arg) {
        m_filePath = arg;
        emit filePathChanged(arg);
    }
}

void setFileReady(bool arg)
{
    if (m_fileReady != arg) {
        m_fileReady = arg;
        emit fileReadyChanged(arg);
    }
}

void setTags(QStringList arg)
{
    if (m_tags != arg) {
        m_tags = arg;
        emit tagsChanged(arg);
    }
}

void setWidth(int arg)
{
    if (m_width != arg) {
        m_width = arg;
        emit widthChanged(arg);
    }
}

void setHeight(int arg)
{
    if (m_height != arg) {
        m_height = arg;
        emit heightChanged(arg);
    }
}

void setauthor(QString arg)
{
    if (m_author != arg) {
        m_author = arg;
        emit authorChanged(arg);
    }
}

void setAuthor(QString arg)
{
    if (m_author != arg) {
        m_author = arg;
        emit authorChanged(arg);
    }
}

private:

SomeEnum m_someEnum;
QString m_id;
QString m_filePath;
bool m_fileReady;
QStringList m_tags;
int m_width;
int m_height;
QString m_author;
};

Q_DECLARE_METATYPE(ISSObject::SomeEnum)

#endif // ISSOBJECT_H
