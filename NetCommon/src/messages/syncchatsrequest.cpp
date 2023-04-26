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

QDateTime SyncChatsRequest::lastUpdate() const
{
    return lastUpdate_;
}

void SyncChatsRequest::setLastUpdate(const QDateTime &newLastUpdate)
{
    lastUpdate_ = newLastUpdate;
}

void SyncChatsRequest::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void SyncChatsRequest::getBodyData(DataStream *stream)
{
    *stream >> fromUsername_ >> lastUpdate_;
}

void SyncChatsRequest::writeBodyData(DataStream *stream) const
{
    *stream << fromUsername_ << lastUpdate_;
}
