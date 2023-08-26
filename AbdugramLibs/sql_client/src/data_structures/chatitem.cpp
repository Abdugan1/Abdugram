#include "data_structures/chatitem.h"

#include <QSqlRecord>
#include <QVariant>
#include <QDataStream>

ChatViewItem::ChatViewItem()
{

}

int ChatViewItem::chatId() const
{
    return chatId_;
}

void ChatViewItem::setChatId(int newId)
{
    chatId_ = newId;
}

QString ChatViewItem::chatName() const
{
    return chatName_;
}

void ChatViewItem::setChatName(const QString &newChatName)
{
    chatName_ = newChatName;
}

QUrl ChatViewItem::pictureUrl() const
{
    return pictureUrl_;
}

void ChatViewItem::setPictureUrl(const QUrl &newPictureUrl)
{
    pictureUrl_ = newPictureUrl;
}

QString ChatViewItem::lastMessage() const
{
    return lastMessage_;
}

void ChatViewItem::setLastMessage(const QString &newLastMessage)
{
    lastMessage_ = newLastMessage;
}

QDateTime ChatViewItem::messageDate() const
{
    return messageDate_;
}

void ChatViewItem::setMessageDate(const QDateTime &newMessageDate)
{
    messageDate_ = newMessageDate;
}

Chat::Type ChatViewItem::chatType() const
{
    return chatType_;
}

void ChatViewItem::setChatType(Chat::Type newChatType)
{
    chatType_ = newChatType;
}

ChatViewItem ChatViewItem::fromSqlRecord(const QSqlRecord &record)
{
    ChatViewItem chatItem;

    chatItem.setChatId(record.value("chat_id").toInt());
    chatItem.setChatName(record.value("chat_name").toString());
    chatItem.setPictureUrl(record.value("picture_url").toUrl());
    chatItem.setChatType(Chat::stringToType(record.value("chat_type").toString()));
    chatItem.setLastMessage(record.value("last_message").toString());
    chatItem.setMessageDate(record.value("message_date").toDateTime());
    chatItem.setUnreadMessageCount(record.value("unread_message_count").toInt());

    return chatItem;
}

int ChatViewItem::unreadMessageCount() const
{
    return unreadMessageCount_;
}

void ChatViewItem::setUnreadMessageCount(int newUnreadMessageCount)
{
    unreadMessageCount_ = newUnreadMessageCount;
}

QDataStream &operator<<(QDataStream &out, const ChatViewItem &chatItem)
{
    out << chatItem.chatId_ << chatItem.chatName_ << chatItem.pictureUrl_
        << chatItem.chatType_ << chatItem.lastMessage_ << chatItem.messageDate_
        << chatItem.unreadMessageCount_;
    return out;
}

QDataStream &operator>>(QDataStream &in, ChatViewItem &chatItem)
{
    in >> chatItem.chatId_ >> chatItem.chatName_ >> chatItem.pictureUrl_
       >> chatItem.chatType_ >> chatItem.lastMessage_ >> chatItem.messageDate_
       >> chatItem.unreadMessageCount_;
    return in;
}
