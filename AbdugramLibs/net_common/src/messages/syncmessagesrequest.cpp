#include "messages/syncmessagesrequest.h"
#include "messages/messagevisitor.h"

SyncMessagesRequest::SyncMessagesRequest()
    : AbduMessage{Type::SyncMessagesRequest}
{

}

void SyncMessagesRequest::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

int SyncMessagesRequest::userId() const
{
    return userId_;
}

void SyncMessagesRequest::setUserId(int newUserId)
{
    userId_ = newUserId;
}

QDateTime SyncMessagesRequest::lastUpdatedAt() const
{
    return lastUpdatedAt_;
}

void SyncMessagesRequest::setLastUpdatedAt(const QDateTime &newLastUpdatedAt)
{
    lastUpdatedAt_ = newLastUpdatedAt;
}

void SyncMessagesRequest::getBodyData(DataStream *stream)
{
    *stream >> userId_ >> lastUpdatedAt_;
}

void SyncMessagesRequest::writeBodyData(DataStream *stream) const
{
    *stream << userId_ << lastUpdatedAt_;
}
