#ifndef SYNCCHATSREPLY_H
#define SYNCCHATSREPLY_H

#include "abdumessage.h"

#include <sql_common/data_structures/chat.h>
#include <sql_common/data_structures/chatuser.h>

class NETCOMMON_EXPORT SyncChatsReply : public AbduMessage
{
public:
    explicit SyncChatsReply();

    void accept(MessageVisitor *visitor) const override;

    QHash<Chat, QList<ChatUser> > unsyncChats() const;
    void setUnsyncChats(const QHash<Chat, QList<ChatUser> > &newChats);

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    QHash<Chat, QList<ChatUser>> unsyncChats_;
};

#endif // SYNCCHATSREPLY_H
