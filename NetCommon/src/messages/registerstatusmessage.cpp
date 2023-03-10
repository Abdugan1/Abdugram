#include "messages/registerstatusmessage.h"

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

void RegisterStatusMessage::gainDataFromPayload(DataStream *stream)
{
    *stream >> success_;
}
