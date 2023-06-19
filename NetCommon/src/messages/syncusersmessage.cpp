#include "messages/syncusersmessage.h"
#include "messages/messagevisitor.h"

SyncUsersMessage::SyncUsersMessage()
    : AbduMessage{Type::SyncUsersMessage}
{

}

void SyncUsersMessage::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void SyncUsersMessage::getBodyData(DataStream *stream)
{
    *stream >> userId_ >> lastUpdatedAt_;
}

void SyncUsersMessage::writeBodyData(DataStream *stream) const
{
    *stream << userId_ << lastUpdatedAt_;
}

QDateTime SyncUsersMessage::lastUpdatedAt() const
{
    return lastUpdatedAt_;
}

void SyncUsersMessage::setLastUpdatedAt(const QDateTime &newLastUpdatedAt)
{
    lastUpdatedAt_ = newLastUpdatedAt;
}

int SyncUsersMessage::userId() const
{
    return userId_;
}

void SyncUsersMessage::setUserId(int newUserId)
{
    userId_ = newUserId;
}
