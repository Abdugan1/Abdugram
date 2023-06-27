#include "messages/registerrequest.h"
#include "messages/messagevisitor.h"

#include <QDebug>

RegisterRequest::RegisterRequest()
    : AbduMessage{Type::Register}
{

}

QString RegisterRequest::firstName() const
{
    return firstName_;
}

void RegisterRequest::setFirstName(const QString &newFirstName)
{
    firstName_ = newFirstName;
}

QString RegisterRequest::username() const
{
    return username_;
}

void RegisterRequest::setUsername(const QString &newUsername)
{
    username_ = newUsername;
}

QString RegisterRequest::password() const
{
    return password_;
}

void RegisterRequest::setPassword(const QString &newPassword)
{
    password_ = newPassword;
}

QString RegisterRequest::phone() const
{
    return phone_;
}

void RegisterRequest::setPhone(const QString &newPhoneNumber)
{
    phone_ = newPhoneNumber;
}

QString RegisterRequest::email() const
{
    return email_;
}

void RegisterRequest::setEmail(const QString &newEmail)
{
    email_ = newEmail;
}

void RegisterRequest::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void RegisterRequest::getBodyData(DataStream *stream)
{
    *stream >> firstName_
            >> username_
            >> password_
            >> phone_
            >> email_;
}

void RegisterRequest::writeBodyData(DataStream *stream) const
{
    *stream << firstName_
            << username_
            << password_
            << phone_
            << email_;
}
