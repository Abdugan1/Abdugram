#include "messages/syncchatsreply.h"
#include "messages/messagevisitor.h"

SyncChatsReply::SyncChatsReply()
    : AbduMessage{Type::SyncChatsReply}
{

}

void SyncChatsReply::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void SyncChatsReply::getBodyData(DataStream *stream)
{
    *stream >> unsyncChats_;
}

void SyncChatsReply::writeBodyData(DataStream *stream) const
{
    *stream << unsyncChats_;
}

QHash<Chat, QList<ChatUser> > SyncChatsReply::unsyncChats() const
{
    return unsyncChats_;
}

void SyncChatsReply::setUnsyncChats(const QHash<Chat, QList<ChatUser> > &newChats)
{
    unsyncChats_ = newChats;
}

