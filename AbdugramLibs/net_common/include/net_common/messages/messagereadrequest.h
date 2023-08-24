#ifndef MESSAGEREADREQUEST_H
#define MESSAGEREADREQUEST_H

#include "abdumessage.h"

#include <sql_common/data_structures/messagereads.h>

#include <QList>

class NETCOMMON_EXPORT MessageReadRequest : public AbduMessage
{
public:
    explicit MessageReadRequest();

    void accept(MessageVisitor *visitor) const override;
    
    QList<MessageRead> messageReads() const;
    void setMessageReads(const QList<MessageRead> &newMessageReads);

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    QList<MessageRead> messageReads_;
};

#endif // MESSAGEREADREQUEST_H
