#ifndef SYNCMESSAGESREPLY_H
#define SYNCMESSAGESREPLY_H

#include "abdumessage.h"

#include <sql_common/data_structures/message.h>

class NETCOMMON_EXPORT SyncMessagesReply : public AbduMessage
{
public:
    explicit SyncMessagesReply();

    void accept(MessageVisitor *visitor) const override;

    QList<Message> unsyncMessages() const;
    void setUnsyncMessages(const QList<Message> &newUnsyncMessages);

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    QList<Message> unsyncMessages_;
};

#endif // SYNCMESSAGESREPLY_H
