#ifndef SYNCMESSAGEREADSREPLY_H
#define SYNCMESSAGEREADSREPLY_H

#include "abdumessage.h"

#include <QList>
class MessageRead;

class NETCOMMON_EXPORT SyncMessageReadsReply : public AbduMessage
{
public:
    explicit SyncMessageReadsReply();

    void accept(MessageVisitor *visitor) const override;

    QList<MessageRead> unsyncMessageReads() const;
    void setUnsyncMessageReads(const QList<MessageRead> &newUnsyncMessageReads);

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    QList<MessageRead> unsyncMessageReads_;
};

#endif // SYNCMESSAGEREADSREPLY_H
