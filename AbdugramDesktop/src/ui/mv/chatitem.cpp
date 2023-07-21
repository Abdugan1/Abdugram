#include "ui/mv/chatitem.h"

ChatItem::ChatItem()
    : ChatModelItem{Type::ChatItem}
{

}

int ChatItem::chatId() const
{
    return chatId_;
}

void ChatItem::setChatId(int newId)
{
    chatId_ = newId;
}

QString ChatItem::chatName() const
{
    return chatName_;
}

void ChatItem::setChatName(const QString &newChatName)
{
    chatName_ = newChatName;
}

QUrl ChatItem::pictureUrl() const
{
    return pictureUrl_;
}

void ChatItem::setPictureUrl(const QUrl &newPictureUrl)
{
    pictureUrl_ = newPictureUrl;
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

QVariant ChatItem::dataImp(int role) const
{
    switch (role) {
    case Roles::ChatId:      return chatId_;      break;
    case Roles::ChatName:    return chatName_;    break;
    case Roles::PictureUrl:  return pictureUrl_;  break;
    case Roles::LastMessage: return lastMessage_; break;
    case Roles::MessageDate: return messageDate_; break;
    case Roles::ChatType:    return chatType_;    break;
    }
    return QVariant{};
}
