#include "abdumessage.h"

AbduMessage::AbduMessage(Type type)
    : type_{type}
{
}

AbduMessage::~AbduMessage()
{

}

AbduMessage::Type AbduMessage::type() const
{
    return type_;
}

void AbduMessage::fromData(const QByteArray &data)
{
    int type;
    DataStream stream(data);
    stream >> type;
}

QByteArray AbduMessage::toData() const
{
    QByteArray data;
    DataStream stream(&data, QIODevice::ReadOnly);

    stream << type();

    return data;
}
