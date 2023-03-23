#include "user.h"

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
