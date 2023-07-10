#include "messages/syncusersrequest.h"
#include "messages/messagevisitor.h"

SyncUsersRequest::SyncUsersRequest()
    : AbduMessage{Type::SyncUsersRequest}
{

}

void SyncUsersRequest::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void SyncUsersRequest::getBodyData(DataStream *stream)
{
    *stream >> userId_ >> lastUpdatedAt_;
}

void SyncUsersRequest::writeBodyData(DataStream *stream) const
{
    *stream << userId_ << lastUpdatedAt_;
}

QDateTime SyncUsersRequest::lastUpdatedAt() const
{
    return lastUpdatedAt_;
}

void SyncUsersRequest::setLastUpdatedAt(const QDateTime &newLastUpdatedAt)
{
    lastUpdatedAt_ = newLastUpdatedAt;
}

int SyncUsersRequest::userId() const
{
    return userId_;
}

void SyncUsersRequest::setUserId(int newUserId)
{
    userId_ = newUserId;
}
