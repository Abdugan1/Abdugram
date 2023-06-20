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

QDateTime SyncChatsRequest::chatsLastUpdatedAt() const
{
    return chatsLastUpdatedAt_;
}

void SyncChatsRequest::setChatsLastUpdatedAt(const QDateTime &newLastUpdate)
{
    chatsLastUpdatedAt_ = newLastUpdate;
}

void SyncChatsRequest::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void SyncChatsRequest::getBodyData(DataStream *stream)
{
    *stream >> userId_ >> chatsLastUpdatedAt_ >> chatUsersLastUpdatedAt_;
}

void SyncChatsRequest::writeBodyData(DataStream *stream) const
{
    *stream << userId_ << chatsLastUpdatedAt_ << chatUsersLastUpdatedAt_;
}

QDateTime SyncChatsRequest::chatUsersLastUpdatedAt() const
{
    return chatUsersLastUpdatedAt_;
}

void SyncChatsRequest::setChatUsersLastUpdatedAt(const QDateTime &newChatUsersLastUpdatedAt)
{
    chatUsersLastUpdatedAt_ = newChatUsersLastUpdatedAt;
}

