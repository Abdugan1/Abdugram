#include "messages/loginstatusmessage.h"

LoginStatusMessage::LoginStatusMessage()
    : AbduMessage{Type::LoginStatus}
{

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

void LoginStatusMessage::gainDataFromPayload(DataStream *stream)
{
    *stream >> success_;
}
