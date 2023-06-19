#include "messages/syncchatsrequest.h"

#include "messages/messagevisitor.h"

SyncChatsRequest::SyncChatsRequest()
    : AbduMessage{Type::SyncChatsRequest}
{
}

int SyncChatsRequest::userId() const
{
    return userId_;
}

void SyncChatsRequest::setUserId(int newUserId)
{
    userId_ = newUserId;
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
    *stream >> userId_ >> lastUpdate_;
}

void SyncChatsRequest::writeBodyData(DataStream *stream) const
{
    *stream << userId_ << lastUpdate_;
}

