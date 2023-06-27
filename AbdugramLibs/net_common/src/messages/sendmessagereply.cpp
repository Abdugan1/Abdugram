#include "messages/sendmessagereply.h"
#include "messages/messagevisitor.h"

SendMessageReply::SendMessageReply()
    : AbduMessage{Type::SendMessageResult}
{

}

Message SendMessageReply::message() const
{
    return message_;
}

void SendMessageReply::setMessage(const Message &newMessage)
{
    message_ = newMessage;
}

void SendMessageReply::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void SendMessageReply::getBodyData(DataStream *stream)
{
    *stream >> message_;
}

void SendMessageReply::writeBodyData(DataStream *stream) const
{
    *stream << message_;
}
