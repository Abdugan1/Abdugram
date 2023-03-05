#include "loginmessage.h"

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

QByteArray LoginMessage::toData() const
{
    QByteArray data = AbduMessage::toData();
    DataStream stream(&data, QIODevice::Append);
    stream << username_ << password_;
    return data;
}

void LoginMessage::gainDataFromPayload(DataStream *stream)
{
    *stream >> username_ >> password_;
}

