#include "messages/messagereadreply.h"
#include "messages/messagevisitor.h"

MessageReadReply::MessageReadReply()
    : AbduMessage{Type::MessageReadReply}
{

}

void MessageReadReply::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

QList<MessageRead> MessageReadReply::messageReads() const
{
    return messageReads_;
}

void MessageReadReply::setMessageReads(const QList<MessageRead> &newMessageReads)
{
    messageReads_ = newMessageReads;
}

void MessageReadReply::getBodyData(DataStream *stream)
{
    *stream >> messageReads_;
}

void MessageReadReply::writeBodyData(DataStream *stream) const
{
    *stream << messageReads_;
}
