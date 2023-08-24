#include "messages/messagereadrequest.h"
#include "messages/messagevisitor.h"

MessageReadRequest::MessageReadRequest()
    : AbduMessage{Type::MessageReadRequest}
{

}

void MessageReadRequest::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

QList<MessageRead> MessageReadRequest::messageReads() const
{
    return messageReads_;
}

void MessageReadRequest::getBodyData(DataStream *stream)
{
    *stream >> messageReads_;
}

void MessageReadRequest::writeBodyData(DataStream *stream) const
{
    *stream << messageReads_;
}

void MessageReadRequest::setMessageReads(const QList<MessageRead> &newMessageReads)
{
    messageReads_ = newMessageReads;
}
