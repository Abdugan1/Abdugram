#include "message.h"

Message::Message()
{
}

int Message::id() const
{
    return id_;
}

void Message::setId(int newId)
{
    id_ = newId;
}

int Message::senderId() const
{
    return senderId_;
}

void Message::setSenderId(int newSenderId)
{
    senderId_ = newSenderId;
}

int Message::conversationId() const
{
    return conversationId_;
}

void Message::setConversationId(int newConversationId)
{
    conversationId_ = newConversationId;
}

const QString &Message::text() const
{
    return text_;
}

void Message::setText(const QString &newText)
{
    text_ = newText;
}

const QDateTime &Message::createdAt() const
{
    return createdAt_;
}

void Message::setCreatedAt(const QDateTime &newCreatedAt)
{
    createdAt_ = newCreatedAt;
}

const QDateTime &Message::updatedAt() const
{
    return updatedAt_;
}

void Message::setUpdatedAt(const QDateTime &newUpdatedAt)
{
    updatedAt_ = newUpdatedAt;
}
