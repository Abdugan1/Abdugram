#include "data_structures/message.h"

#include <QDataStream>
#include <QSqlRecord>
#include <QVariant>

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

int Message::chatId() const
{
    return chatId_;
}

void Message::setChatId(int newChatId)
{
    chatId_ = newChatId;
}

int Message::senderId() const
{
    return senderId_;
}

void Message::setSenderId(int newSenderId)
{
    senderId_ = newSenderId;
}

int Message::replyToId() const
{
    return replyToId_;
}

void Message::setReplyToId(int newReplyToId)
{
    replyToId_ = newReplyToId;
}

QString Message::text() const
{
    return text_;
}

void Message::setText(const QString &newText)
{
    text_ = newText;
}

bool Message::isEdited() const
{
    return isEdited_;
}

void Message::setIsEdited(bool newIsEdited)
{
    isEdited_ = newIsEdited;
}

QDateTime Message::createdAt() const
{
    return createdAt_;
}

void Message::setCreatedAt(const QDateTime &newCreatedAt)
{
    createdAt_ = newCreatedAt;
}

QDateTime Message::updatedAt() const
{
    return updatedAt_;
}

void Message::setUpdatedAt(const QDateTime &newUpdatedAt)
{
    updatedAt_ = newUpdatedAt;
}

Message Message::fromSqlRecord(const QSqlRecord &record)
{
    Message message;

    message.setId(record.value("id").toInt());
    message.setChatId(record.value("chat_id").toInt());
    message.setSenderId(record.value("sender_id").toInt());

    const int replyToId = record.value("reply_to_id").toInt();
    message.setReplyToId(replyToId > 0 ? replyToId : -1);

    message.setText(record.value("text").toString());
    message.setIsEdited(record.value("is_edited").toBool());
    message.setCreatedAt(record.value("created_at").toDateTime());
    message.setUpdatedAt(record.value("updated_at").toDateTime());

    return message;
}

QDataStream &operator<<(QDataStream &out, const Message &message)
{
    out << message.id_        << message.chatId_    << message.senderId_
        << message.replyToId_ << message.text_      << message.isEdited_
        << message.createdAt_ << message.updatedAt_;
    return out;
}

QDataStream &operator>>(QDataStream &in, Message &message)
{
    in >> message.id_        >> message.chatId_    >> message.senderId_
       >> message.replyToId_ >> message.text_      >> message.isEdited_
       >> message.createdAt_ >> message.updatedAt_;
    return in;
}
