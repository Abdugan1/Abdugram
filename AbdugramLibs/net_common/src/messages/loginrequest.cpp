#include "messages/loginrequest.h"
#include "messages/messagevisitor.h"

LoginRequest::LoginRequest()
    : AbduMessage{Type::LoginRequest}
{

}

QString LoginRequest::username() const
{
    return username_;
}

void LoginRequest::setUsername(const QString &newUsername)
{
    username_ = newUsername;
}

QString LoginRequest::password() const
{
    return password_;
}

void LoginRequest::setPassword(const QString &newPassword)
{
    password_ = newPassword;
}

void LoginRequest::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void LoginRequest::getBodyData(DataStream *stream)
{
    *stream >> username_ >> password_;
}

void LoginRequest::writeBodyData(DataStream *stream) const
{
    *stream << username_ << password_;
}

