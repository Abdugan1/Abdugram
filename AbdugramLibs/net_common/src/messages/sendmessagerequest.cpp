#include "messages/sendmessagerequest.h"
#include "messages/messagevisitor.h"

SendMessageRequest::SendMessageRequest()
    : AbduMessage{Type::SendMessageRequest}
{

}

Message SendMessageRequest::message() const
{
    return message_;
}

void SendMessageRequest::setMessage(const Message &newMessage)
{
    message_ = newMessage;
}

void SendMessageRequest::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void SendMessageRequest::getBodyData(DataStream *stream)
{
    *stream >> message_;
}

void SendMessageRequest::writeBodyData(DataStream *stream) const
{
    *stream << message_;
}
