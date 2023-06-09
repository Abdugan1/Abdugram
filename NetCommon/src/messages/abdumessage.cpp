#include "messages/abdumessage.h"

#include <QDebug>

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
    DataStream stream(data);

    getHeaderData(&stream);
    getBodyData(&stream);
}

QByteArray AbduMessage::toData() const
{
    QByteArray data;
    DataStream stream(&data, QIODevice::WriteOnly);

    writeHeaderData(&stream);
    writeBodyData(&stream);

    return data;
}

int AbduMessage::headerSize() const
{
    return 4;
}

void AbduMessage::accept(MessageVisitor *visitor) const
{
    Q_UNUSED(visitor);
    qWarning() << "Accepting in base class AbduMessage!";
}

void AbduMessage::getBodyData(DataStream *stream)
{
    Q_UNUSED(stream);
    qWarning() << "Gaining from body from base class AbduMessage!";
}

void AbduMessage::writeBodyData(DataStream *stream) const
{
    Q_UNUSED(stream);
    qWarning() << "Writing to bodyfrom base class AbduMessage!";
}

void AbduMessage::getHeaderData(DataStream *stream)
{
    int type;
    *stream >> type; // For now unnecessary but required
}

void AbduMessage::writeHeaderData(DataStream *stream) const
{
    *stream << type();
}
