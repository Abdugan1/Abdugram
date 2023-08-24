#include "messages/syncmessagereadsreply.h"
#include "messages/messagevisitor.h"

#include <sql_common/data_structures/messagereads.h>
SyncMessageReadsReply::SyncMessageReadsReply()
    : AbduMessage{Type::SyncMessageReadsReply}
{

}

void SyncMessageReadsReply::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void SyncMessageReadsReply::getBodyData(DataStream *stream)
{
    *stream >> unsyncMessageReads_;
}

void SyncMessageReadsReply::writeBodyData(DataStream *stream) const
{
    *stream << unsyncMessageReads_;
}

QList<MessageRead> SyncMessageReadsReply::unsyncMessageReads() const
{
    return unsyncMessageReads_;
}

void SyncMessageReadsReply::setUnsyncMessageReads(const QList<MessageRead> &newUnsyncMessageReads)
{
    unsyncMessageReads_ = newUnsyncMessageReads;
}
