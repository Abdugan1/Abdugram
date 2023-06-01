#ifndef CHAT_H
#define CHAT_H

#include "../SqlCommon_global.h"

#include <QDateTime>

class QSqlRecord;

class SQLCOMMON_EXPORT Chat
{
public:
    enum Type {
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

    int createdByUserId() const;
    void setCreatedByUserId(int newCreatedByUserId);

    QDateTime createdAt() const;
    void setCreatedAt(const QDateTime &newCreatedAt);

    QDateTime updatedAt() const;
    void setUpdatedAt(const QDateTime &newUpdatedAt);

    QDateTime deletedAt() const;
    void setDeletedAt(const QDateTime &newDeletedAt);

private:
    int id_ = -1;
    QString name_;
    QString description_;
    Type type_ = Type::Private;
    int createdByUserId_ = -1;
    QDateTime createdAt_;
    QDateTime updatedAt_;
    QDateTime deletedAt_;

};

QDataStream &operator<<(QDataStream &out, const Chat &chat);
QDataStream &operator>>(QDataStream &in, Chat &chat);

extern Chat getChatFromQueryResult(const QSqlRecord &record);

#endif // CHAT_H
