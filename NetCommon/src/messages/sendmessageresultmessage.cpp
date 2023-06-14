#include "messages/sendmessageresultmessage.h"
#include "messages/messagevisitor.h"

SendMessageResultMessage::SendMessageResultMessage()
    : AbduMessage{Type::SendMessageResult}
{

}

Message SendMessageResultMessage::message() const
{
    return message_;
}

void SendMessageResultMessage::setMessage(const Message &newMessage)
{
    message_ = newMessage;
}

void SendMessageResultMessage::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void SendMessageResultMessage::getBodyData(DataStream *stream)
{
    *stream >> message_;
}

void SendMessageResultMessage::writeBodyData(DataStream *stream) const
{
    *stream << message_;
}
