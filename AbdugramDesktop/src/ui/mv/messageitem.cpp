#include "ui/mv/messageitem.h"

#include <sql_common/data_structures/message.h>

#include <QVariant>
#include <QDebug>

MessageItem::MessageItem()
    : MessageModelItem{Type::MessageItem}
{
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

    messageItem->setSenderId(message.senderId());
    messageItem->setText(message.text());
    messageItem->setDateTime(message.createdAt());

    return messageItem;
}

QVariant MessageItem::dataImp(int role) const
{
    switch (static_cast<Roles>(role)) {
    case Roles::SenderId: return senderId_; break;
    case Roles::Text:     return text_;     break;
    case Roles::DateTime: return dateTime_; break;
    }
    return QVariant{};
}
