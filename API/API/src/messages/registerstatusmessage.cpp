#include "registerstatusmessage.h"

RegisterStatusMessage::RegisterStatusMessage()
    : AbduMessage{Type::RegisterStaus}
{

}

void RegisterStatusMessage::fromData(const QByteArray &data)
{
    AbduMessage::fromData(data);
    DataStream stream(data);
    stream >> success_;
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
