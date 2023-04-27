#include "user.h"

#include <QDataStream>

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

QDataStream &operator<<(QDataStream &out, const User &user)
{
    out << user.id()       << user.username() << user.firstName()
        << user.lastName() << user.email()    << user.phone();
    return out;
}

QDataStream &operator>>(QDataStream &in, User &user)
{
    int id;
    QString username;
    QString firstName;
    QString lastName;
    QString email;
    QString phone;

    in >> id       >> username >> firstName
       >> lastName >> email    >> phone;

    user.setId(id);
    user.setUsername(username);
    user.setFirstName(firstName);
    user.setLastName(lastName);
    user.setEmail(email);
    user.setPhone(phone);

    return in;
}
