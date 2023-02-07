#include "loginstatusmessage.h"

LoginStatusMessage::LoginStatusMessage()
    : AbduMessage{Type::LoginStatus}
{

}

void LoginStatusMessage::fromData(const QByteArray &data)
{
    AbduMessage::fromData(data);
    DataStream stream(data);
    stream >> success_;
}

QByteArray LoginStatusMessage::toData() const
{
    QByteArray data = AbduMessage::toData();
    DataStream stream(&data, QIODevice::Append);
    stream << success_;
    return data;
}

bool LoginStatusMessage::success() const
{
    return success_;
}

void LoginStatusMessage::setSuccess(bool newSuccess)
{
    success_ = newSuccess;
}
