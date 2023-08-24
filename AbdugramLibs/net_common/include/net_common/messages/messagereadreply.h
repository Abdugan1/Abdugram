#ifndef MESSAGEREADREPLY_H
#define MESSAGEREADREPLY_H

#include "abdumessage.h"

#include <sql_common/data_structures/messagereads.h>

#include <QList>
#include <QDateTime>

class NETCOMMON_EXPORT MessageReadReply : public AbduMessage
{
public:
    explicit MessageReadReply();

    void accept(MessageVisitor *visitor) const override;
    
    QList<MessageRead> messageReads() const;
    void setMessageReads(const QList<MessageRead> &newMessageReads);

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    QList<MessageRead> messageReads_;
};

#endif // MESSAGEREADREPLY_H
