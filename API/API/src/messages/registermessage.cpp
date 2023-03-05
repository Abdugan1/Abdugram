#include "registermessage.h"

#include <QDebug>

RegisterMessage::RegisterMessage()
    : AbduMessage{Type::Register}
{

}

QByteArray RegisterMessage::toData() const
{
    QByteArray data = AbduMessage::toData();
    DataStream stream(&data, QIODevice::Append);
    stream << firstName_
           << lastName_
           << username_
           << password_
           << phone_
           << email_;

    return data;
}

QString RegisterMessage::firstName() const
{
    return firstName_;
}

void RegisterMessage::setFirstName(const QString &newFirstName)
{
    firstName_ = newFirstName;
}

QString RegisterMessage::lastName() const
{
    return lastName_;
}

void RegisterMessage::setLastName(const QString &newLastName)
{
    lastName_ = newLastName;
}

QString RegisterMessage::username() const
{
    return username_;
}

void RegisterMessage::setUsername(const QString &newUsername)
{
    username_ = newUsername;
}

QString RegisterMessage::password() const
{
    return password_;
}

void RegisterMessage::setPassword(const QString &newPassword)
{
    password_ = newPassword;
}

QString RegisterMessage::phone() const
{
    return phone_;
}

void RegisterMessage::setPhone(const QString &newPhoneNumber)
{
    phone_ = newPhoneNumber;
}

QString RegisterMessage::email() const
{
    return email_;
}

void RegisterMessage::setEmail(const QString &newEmail)
{
    email_ = newEmail;
}

void RegisterMessage::gainDataFromPayload(DataStream *stream)
{
    *stream >> firstName_
            >> lastName_
            >> username_
            >> password_
            >> phone_
            >> email_;
}
