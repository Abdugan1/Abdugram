#include "user.h"
#include "fields.h"

User::User()
{

}

int User::id() const
{
    return id_;
}

void User::setId(int newId)
{
    id_ = newId;
}

QDateTime User::createdAt() const
{
    return createdAt_;
}

void User::setCreatedAt(const QDateTime &newCreatedAt)
{
    createdAt_ = newCreatedAt;
}

QDateTime User::updatedAt() const
{
    return updatedAt_;
}

void User::setUpdatedAt(const QDateTime &newUpdatedAt)
{
    updatedAt_ = newUpdatedAt;
}

QDateTime User::deletedAt() const
{
    return deletedAt_;
}

void User::setDeletedAt(const QDateTime &newDeletedAt)
{
    deletedAt_ = newDeletedAt;
}

QJsonObject User::toJson(const User &user)
{
    using namespace fieldnames::user;
    QJsonObject json;

    json[Id]        = user.id();
    json[CreatedAt] = user.createdAt().toString(Qt::ISODate);
    json[UpdatedAt] = user.updatedAt().toString(Qt::ISODate);
    json[DeletedAt] = user.deletedAt().toString(Qt::ISODate);

    return json;
}

User User::fromJson(const QJsonObject &json)
{
    using namespace fieldnames::user;

    auto toDateTime = [](const QJsonValue &value) {
        return QDateTime::fromString(value.toString(), Qt::ISODate);
    };

    User user;

    user.setId(json[Id].toInt());
    user.setCreatedAt(toDateTime(json[CreatedAt]));
    user.setUpdatedAt(toDateTime(json[UpdatedAt]));
    user.setDeletedAt(toDateTime(json[DeletedAt]));

    return user;
}
