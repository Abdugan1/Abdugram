#include "ui/mv/chatitem.h"

ChatItem::ChatItem()
{

}

QUrl ChatItem::avatar() const
{
    return avatar_;
}

void ChatItem::setAvatar(const QUrl &newAvatar)
{
    avatar_ = newAvatar;
}

QString ChatItem::chatName() const
{
    return chatName_;
}

void ChatItem::setChatName(const QString &newChatName)
{
    chatName_ = newChatName;
}

QString ChatItem::lastMessage() const
{
    return lastMessage_;
}

void ChatItem::setLastMessage(const QString &newLastMessage)
{
    lastMessage_ = newLastMessage;
}

QDateTime ChatItem::messageDate() const
{
    return messageDate_;
}

void ChatItem::setMessageDate(const QDateTime &newMessageDate)
{
    messageDate_ = newMessageDate;
}

Chat::Type ChatItem::chatType() const
{
    return chatType_;
}

void ChatItem::setChatType(Chat::Type newChatType)
{
    chatType_ = newChatType;
}

int ChatItem::chatId() const
{
    return chatId_;
}

void ChatItem::setChatId(int newId)
{
    chatId_ = newId;
}
