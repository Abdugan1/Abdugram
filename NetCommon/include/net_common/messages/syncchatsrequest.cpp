#include "messages/syncchatsrequest.h"

#include "messages/messagevisitor.h"

SyncChatsRequest::SyncChatsRequest()
    : AbduMessage{Type::SyncChatsRequest}
{

}

QString SyncChatsRequest::fromUsername() const
{
    return fromUsername_;
}

void SyncChatsRequest::setFromUsername(const QString &newFromUsername)
{
    fromUsername_ = newFromUsername;
}

QString SyncChatsRequest::lastUpdate() const
{
    return lastUpdate_;
}

void SyncChatsRequest::setLastUpdate(const QString &newLastUpdate)
{
    lastUpdate_ = newLastUpdate;
}

QByteArray SyncChatsRequest::toData() const
{
    QByteArray data = AbduMessage::toData();
    DataStream stream(&data, QIODevice::Append);
    stream << fromUsername_ << lastUpdate_;
    return data;
}

void SyncChatsRequest::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void SyncChatsRequest::gainDataFromPayload(DataStream *stream)
{
    *stream >> fromUsername_ >> lastUpdate_;
}
