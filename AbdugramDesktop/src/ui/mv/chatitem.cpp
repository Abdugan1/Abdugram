#include "ui/mv/chatitem.h"

ChatItem::ChatItem()
    : ChatModelItem{Type::ChatItem}
{

}

int ChatItem::chatId() const
{
    return chatView_.chatId();
}

void ChatItem::setChatId(int newChatId)
{
    chatView_.setChatId(newChatId);
}

QString ChatItem::chatName() const
{
    return chatView_.chatName();
}

void ChatItem::setChatName(const QString &newChatName)
{
    chatView_.setChatName(newChatName);
}

QUrl ChatItem::pictureUrl() const
{
    return chatView_.pictureUrl();
}

void ChatItem::setPictureName(const QUrl &newPictureUrl)
{
    chatView_.setPictureUrl(newPictureUrl);
}

QString ChatItem::lastMessage() const
{
    return chatView_.lastMessage();
}

void ChatItem::setLastMessage(const QString &newLastMessage)
{
    chatView_.setLastMessage(newLastMessage);
}

QDateTime ChatItem::messageDate() const
{
    return chatView_.messageDate();
}

void ChatItem::setMessageDate(const QDateTime &newMessageDate)
{
    chatView_.setMessageDate(newMessageDate);
}

Chat::Type ChatItem::chatType() const
{
    return chatView_.chatType();
}

void ChatItem::setChatType(Chat::Type newChatType)
{
    chatView_.setChatType(newChatType);
}

ChatItemPtr ChatItem::fromChatViewItem(const ChatViewItem &newChatView)
{
    ChatItemPtr chatItem{new ChatItem};
    chatItem->chatView_ = newChatView;
    return chatItem;
}

QVariant ChatItem::dataImp(int role) const
{
    switch (role) {
    case Roles::ChatId:      return chatId();      break;
    case Roles::ChatName:    return chatName();    break;
    case Roles::PictureUrl:  return pictureUrl();  break;
    case Roles::LastMessage: return lastMessage(); break;
    case Roles::MessageDate: return messageDate(); break;
    case Roles::ChatType:    return chatType();    break;
    }
    return QVariant{};
}
