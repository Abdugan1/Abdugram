#include "messages/messagesupdated.h"
#include "messages/messagevisitor.h"

#include <sql_common/data_structures/message.h>

MessagesUpdated::MessagesUpdated()
    : AbduMessage{Type::MessagesUpdated}
{

}

void MessagesUpdated::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void MessagesUpdated::getBodyData(DataStream *stream)
{
    *stream >> messages_;
}

void MessagesUpdated::writeBodyData(DataStream *stream) const
{
    *stream << messages_;
}

QList<Message> MessagesUpdated::messages() const
{
    return messages_;
}

void MessagesUpdated::setMessages(const QList<Message> &newMessages)
{
    messages_ = newMessages;
}
