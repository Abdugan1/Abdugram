#include "messages/sendmessagemessage.h"
#include "messages/messagevisitor.h"

SendMessageMessage::SendMessageMessage()
    : AbduMessage{Type::SendMessage}
{

}

Message SendMessageMessage::message() const
{
    return message_;
}

void SendMessageMessage::setMessage(const Message &newMessage)
{
    message_ = newMessage;
}

void SendMessageMessage::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void SendMessageMessage::getBodyData(DataStream *stream)
{
    *stream >> message_;
}

void SendMessageMessage::writeBodyData(DataStream *stream) const
{
    *stream << message_;
}
