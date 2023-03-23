#include "messages/registerstatusmessage.h"
#include "messages/messagevisitor.h"

RegisterStatusMessage::RegisterStatusMessage()
    : AbduMessage{Type::RegisterStaus}
{

}

QByteArray RegisterStatusMessage::toData() const
{
    QByteArray data = AbduMessage::toData();
    DataStream stream(&data, QIODevice::Append);
    stream << success_;
    return data;
}

bool RegisterStatusMessage::success() const
{
    return success_;
}

void RegisterStatusMessage::setSuccess(bool newSuccess)
{
    success_ = newSuccess;
}

void RegisterStatusMessage::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void RegisterStatusMessage::gainDataFromPayload(DataStream *stream)
{
    *stream >> success_;
}
