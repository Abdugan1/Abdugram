#include "ui/mv/messageitem.h"

#include <sql_common/data_structures/message.h>

MessageItem::MessageItem()
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

MessageItem MessageItem::fromMessage(const Message &message)
{
    MessageItem messageItem;

    messageItem.setSenderId(message.senderId());
    messageItem.setText(message.text());
    messageItem.setDateTime(message.createdAt());

    return messageItem;
}
