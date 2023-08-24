#include "data_structures/messagereads.h"

#include <QSqlRecord>

MessageRead::MessageRead()
{

}

int MessageRead::userId() const
{
    return userId_;
}

void MessageRead::setUserId(int newUserId)
{
    userId_ = newUserId;
}

int MessageRead::messageId() const
{
    return messageId_;
}

void MessageRead::setMessageId(int newMessageId)
{
    messageId_ = newMessageId;
}

QDateTime MessageRead::readTime() const
{
    return readTime_;
}

void MessageRead::setReadTime(const QDateTime &newReadTime)
{
    readTime_ = newReadTime;
}

MessageRead MessageRead::fromSqlRecord(const QSqlRecord &record)
{
    MessageRead messageReads;
    messageReads.setUserId(record.value("user_id").toInt());
    messageReads.setMessageId(record.value("message_id").toInt());
    messageReads.setReadTime(record.value("read_at").toDateTime());
    messageReads.setCreatedAt(record.value("created_at").toDateTime());
    messageReads.setUpdatedAt(record.value("updated_at").toDateTime());
    return messageReads;
}

QDateTime MessageRead::createdAt() const
{
    return createdAt_;
}

void MessageRead::setCreatedAt(const QDateTime &newCreatedAt)
{
    createdAt_ = newCreatedAt;
}

QDateTime MessageRead::updatedAt() const
{
    return updatedAt_;
}

void MessageRead::setUpdatedAt(const QDateTime &newUpdatedAt)
{
    updatedAt_ = newUpdatedAt;
}

QDataStream &operator<<(QDataStream &out, const MessageRead &messageReads)
{
    out << messageReads.userId_    << messageReads.messageId_ << messageReads.readTime_
        << messageReads.createdAt_ << messageReads.updatedAt_;
    return out;
}

QDataStream &operator>>(QDataStream &in, MessageRead &messageReads)
{
    in >> messageReads.userId_    >> messageReads.messageId_ >> messageReads.readTime_
       >> messageReads.createdAt_ >> messageReads.updatedAt_;
    return in;
}
