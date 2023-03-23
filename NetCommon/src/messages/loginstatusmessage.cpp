#include "messages/loginstatusmessage.h"
#include "messages/messagevisitor.h"

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

void LoginStatusMessage::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void LoginStatusMessage::gainDataFromPayload(DataStream *stream)
{
    *stream >> success_;
}
