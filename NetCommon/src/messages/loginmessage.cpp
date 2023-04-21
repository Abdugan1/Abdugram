#include "messages/loginmessage.h"

#include "messages/messagevisitor.h"

LoginMessage::LoginMessage()
    : AbduMessage{Type::Login}
{

}

QString LoginMessage::username() const
{
    return username_;
}

void LoginMessage::setUsername(const QString &newUsername)
{
    username_ = newUsername;
}

QString LoginMessage::password() const
{
    return password_;
}

void LoginMessage::setPassword(const QString &newPassword)
{
    password_ = newPassword;
}

void LoginMessage::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void LoginMessage::getBodyData(DataStream *stream)
{
    *stream >> username_ >> password_;
}

void LoginMessage::writeBodyData(DataStream *stream) const
{
    *stream << username_ << password_;
}

