#ifndef SYNCMESSAGESREQUEST_H
#define SYNCMESSAGESREQUEST_H

#include "abdumessage.h"

#include <QDateTime>

class NETCOMMON_EXPORT SyncMessagesRequest : public AbduMessage
{
public:
    explicit SyncMessagesRequest();

    void accept(MessageVisitor *visitor) const override;

    int userId() const;
    void setUserId(int newUserId);

    QDateTime lastUpdatedAt() const;
    void setLastUpdatedAt(const QDateTime &newLastUpdatedAt);

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    int userId_ = 1;
    QDateTime lastUpdatedAt_;
};

#endif // SYNCMESSAGESREQUEST_H
