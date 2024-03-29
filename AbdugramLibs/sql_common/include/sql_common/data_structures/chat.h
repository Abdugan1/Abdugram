#ifndef CHAT_H
#define CHAT_H

#include "../SqlCommon_global.h"

#include <QDateTime>

class QSqlRecord;

class SQLCOMMON_EXPORT Chat
{
public:
    enum Type {
        Unknown,
        Private,
        Group,
        Channel,
    };

    explicit Chat();

    int id() const;
    void setId(int newId);

    QString name() const;
    void setName(const QString &newName);

    QString description() const;
    void setDescription(const QString &newDescription);

    Type type() const;
    void setType(Type newType);

    QDateTime createdAt() const;
    void setCreatedAt(const QDateTime &newCreatedAt);

    QDateTime updatedAt() const;
    void setUpdatedAt(const QDateTime &newUpdatedAt);

    QDateTime deletedAt() const;
    void setDeletedAt(const QDateTime &newDeletedAt);

    static QString typeToString(Type type);
    static Type stringToType(const QString &str);

    static Chat fromSqlRecord(const QSqlRecord &record);

    SQLCOMMON_EXPORT friend QDataStream &operator<<(QDataStream &out, const Chat &chat);
    SQLCOMMON_EXPORT friend QDataStream &operator>>(QDataStream &in, Chat &chat);

    SQLCOMMON_EXPORT friend bool operator==(const Chat &chat1, const Chat &chat2);

    SQLCOMMON_EXPORT friend uint qHash(const Chat& chat);

private:
    int id_ = -1;
    QString name_;
    QString description_;
    Type type_ = Type::Private;
    QDateTime createdAt_;
    QDateTime updatedAt_;
    QDateTime deletedAt_;
};

#endif // CHAT_H
