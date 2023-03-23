#include "messages/abdumessage.h"

#include <QDebug>

AbduMessage::AbduMessage(Type type)
    : type_{type}
{
    qDebug() << "Constructor:" << typeid(this).name();
}

AbduMessage::~AbduMessage()
{
    qDebug() << "Destructor:" << typeid(this).name();
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

    gainDataFromPayload(&stream);
}

QByteArray AbduMessage::toData() const
{
    QByteArray data;
    DataStream stream(&data, QIODevice::WriteOnly);

    stream << type();

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

void AbduMessage::gainDataFromPayload(DataStream *stream)
{
    Q_UNUSED(stream);
    qWarning() << "Gaining payload from base class AbduMessage!";
}
