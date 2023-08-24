#include "ui/mv/messageitem.h"

#include <sql_common/data_structures/message.h>

#include <QVariant>
#include <QDebug>

MessageItem::MessageItem()
    : MessageModelItem{Type::MessageItem}
{
}

int MessageItem::messageId() const
{
    return messageId_;
}

void MessageItem::setMessageId(int newMessageId)
{
    messageId_ = newMessageId;
}


int MessageItem::senderId() const
{
    return senderId_;
}

void MessageItem::setSenderId(int newSenderId)
{
    senderId_ = newSenderId;
}

QString MessageItem::text() const
{
    return text_;
}

void MessageItem::setText(const QString &newText)
{
    text_ = newText;
}

QDateTime MessageItem::dateTime() const
{
    return dateTime_;
}

void MessageItem::setDateTime(const QDateTime &newDateTime)
{
    dateTime_ = newDateTime;
}

MessageItemPtr MessageItem::fromMessage(const Message &message)
{
    MessageItemPtr messageItem{new MessageItem};

    messageItem->setMessageId(message.id());
    messageItem->setSenderId(message.senderId());
    messageItem->setText(message.text());
    messageItem->setDateTime(message.createdAt());
    messageItem->setIsRead(message.isRead());
    messageItem->setIsEdited(message.isEdited());

    return messageItem;
}

QVariant MessageItem::dataImp(int role) const
{
    switch (static_cast<Roles>(role)) {
    case Roles::MessageId: return messageId_; break;
    case Roles::SenderId:  return senderId_;  break;
    case Roles::Text:      return text_;      break;
    case Roles::DateTime:  return dateTime_;  break;
    case Roles::IsRead:    return isRead_;    break;
    case Roles::IsEdited:  return isEdited_;  break;
    }
    return QVariant{};
}

bool MessageItem::isEdited() const
{
    return isEdited_;
}

void MessageItem::setIsEdited(bool newIsEdited)
{
    isEdited_ = newIsEdited;
}

bool MessageItem::isRead() const
{
    return isRead_;
}

void MessageItem::setIsRead(bool newIsRead)
{
    isRead_ = newIsRead;
}

void MessageItem::setData(int role, const QVariant &data)
{
    switch (static_cast<Roles>(role)) {
    case Roles::MessageId: setMessageId(data.toInt());     break;
    case Roles::SenderId:  setSenderId(data.toInt());      break;
    case Roles::Text:      setText(data.toString());       break;
    case Roles::DateTime:  setDateTime(data.toDateTime()); break;
    case Roles::IsRead:    setIsRead(data.toBool());       break;
    case Roles::IsEdited:  setIsEdited(data.toBool());     break;
    }
}
