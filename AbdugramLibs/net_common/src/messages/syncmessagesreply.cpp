#include "messages/syncmessagesreply.h"
#include "messages/messagevisitor.h"

SyncMessagesReply::SyncMessagesReply()
    : AbduMessage{Type::SyncMessagesReply}
{

}

void SyncMessagesReply::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

QList<Message> SyncMessagesReply::unsyncMessages() const
{
    return unsyncMessages_;
}

void SyncMessagesReply::setUnsyncMessages(const QList<Message> &newUnsyncMessages)
{
    unsyncMessages_ = newUnsyncMessages;
}

void SyncMessagesReply::getBodyData(DataStream *stream)
{
    *stream >> unsyncMessages_;
}

void SyncMessagesReply::writeBodyData(DataStream *stream) const
{
    *stream << unsyncMessages_;
}
