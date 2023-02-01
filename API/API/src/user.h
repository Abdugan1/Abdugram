#ifndef USER_H
#define USER_H

#include "API_global.h"

#include <QJsonObject>

#include <QDateTime>
#include <QObject>

class API_EXPORT User
{
    Q_GADGET
    Q_PROPERTY(int id READ id WRITE setId)
    Q_PROPERTY(QDateTime createdAt READ createdAt WRITE setCreatedAt)
    Q_PROPERTY(QDateTime updatedAt READ updatedAt WRITE setUpdatedAt)
    Q_PROPERTY(QDateTime deletedAt READ deletedAt WRITE setDeletedAt)
public:
    explicit User();

    int id() const;
    void setId(int newId);

    QDateTime createdAt() const;
    void setCreatedAt(const QDateTime &newCreatedAt);

    QDateTime updatedAt() const;
    void setUpdatedAt(const QDateTime &newUpdatedAt);

    QDateTime deletedAt() const;
    void setDeletedAt(const QDateTime &newDeletedAt);

    static QJsonObject toJson(const User &user);
    static User        fromJson(const QJsonObject &json);

private:
    int id_ = -1;
    QDateTime createdAt_;
    QDateTime updatedAt_;
    QDateTime deletedAt_;
};

#endif // USER_H
