#include "messages/syncmessagereadsrequest.h"
#include "messages/messagevisitor.h"

SyncMessageReadsRequest::SyncMessageReadsRequest()
    : AbduMessage{Type::SyncMessageReadsRequest}
{

}

void SyncMessageReadsRequest::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void SyncMessageReadsRequest::getBodyData(DataStream *stream)
{
    *stream >> userId_ >> lastUpdatedAt_;
}

void SyncMessageReadsRequest::writeBodyData(DataStream *stream) const
{
    *stream << userId_ << lastUpdatedAt_;
}

int SyncMessageReadsRequest::userId() const
{
    return userId_;
}

void SyncMessageReadsRequest::setUserId(int newUserId)
{
    userId_ = newUserId;
}

QDateTime SyncMessageReadsRequest::lastUpdatedAt() const
{
    return lastUpdatedAt_;
}

void SyncMessageReadsRequest::setLastUpdatedAt(const QDateTime &newLastUpdatedAt)
{
    lastUpdatedAt_ = newLastUpdatedAt;
}
