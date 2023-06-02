#include "data_structures/user.h"
#include "functions.h"

#include <QDataStream>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

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

QString User::username() const
{
    return username_;
}

void User::setUsername(const QString &newUsername)
{
    username_ = newUsername;
}

QString User::firstName() const
{
    return firstName_;
}

void User::setFirstName(const QString &newFirstName)
{
    firstName_ = newFirstName;
}

QString User::lastName() const
{
    return lastName_;
}

void User::setLastName(const QString &newLastName)
{
    lastName_ = newLastName;
}

QString User::email() const
{
    return email_;
}

void User::setEmail(const QString &newEmail)
{
    email_ = newEmail;
}

QString User::phone() const
{
    return phone_;
}

void User::setPhone(const QString &newPhone)
{
    phone_ = newPhone;
}

QString User::avatarUrl() const
{
    return avatarUrl_;
}

void User::setAvatarUrl(const QString &newAvatarUrl)
{
    avatarUrl_ = newAvatarUrl;
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

QDateTime User::lastTimeOnline() const
{
    return lastTimeOnline_;
}

void User::setLastTimeOnline(const QDateTime &newLastTimeOnline)
{
    lastTimeOnline_ = newLastTimeOnline;
}

bool User::isOnline() const
{
    return isOnline_;
}

void User::setIsOnline(bool newIsOnline)
{
    isOnline_ = newIsOnline;
}

bool User::isDeleted() const
{
    return isDeleted_;
}

void User::setIsDeleted(bool newIsDeleted)
{
    isDeleted_ = newIsDeleted;
}

User User::fromSqlRecord(const QSqlRecord &record)
{
    User user;

    user.setId(record.value("id").toInt());
    user.setUsername(record.value("username").toString());
    user.setFirstName(record.value("first_name").toString());
    user.setLastName(record.value("last_name").toString());
    user.setEmail(record.value("email").toString());
    user.setPhone(record.value("phone").toString());
    user.setAvatarUrl(record.value("avatar_url").toString());
    user.setCreatedAt(record.value("created_at").toDateTime());
    user.setUpdatedAt(record.value("updated_at").toDateTime());
    user.setLastTimeOnline(record.value("last_time_online").toDateTime());
    user.setIsOnline(record.value("isOnline").toBool());
    user.setIsDeleted(record.value("is_deleted").toBool());

    return user;
}

QDataStream &operator<<(QDataStream &out, const User &user)
{
    out << user.id_             << user.username_  << user.firstName_
        << user.lastName_       << user.email_     << user.phone_
        << user.avatarUrl_      << user.createdAt_ << user.updatedAt_
        << user.lastTimeOnline_ << user.isOnline_  << user.isDeleted_;
    return out;
}

QDataStream &operator>>(QDataStream &in, User &user)
{
    in >> user.id_             >> user.username_  >> user.firstName_
       >> user.lastName_       >> user.email_     >> user.phone_
       >> user.avatarUrl_      >> user.createdAt_ >> user.updatedAt_
       >> user.lastTimeOnline_ >> user.isOnline_  >> user.isDeleted_;
    return in;
}
