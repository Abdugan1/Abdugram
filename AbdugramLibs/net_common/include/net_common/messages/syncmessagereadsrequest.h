#ifndef SYNCMESSAGEREADSREQUEST_H
#define SYNCMESSAGEREADSREQUEST_H

#include "abdumessage.h"

#include <QDateTime>

class NETCOMMON_EXPORT SyncMessageReadsRequest : public AbduMessage
{
public:
    explicit SyncMessageReadsRequest();

    void accept(MessageVisitor *visitor) const override;

    QDateTime lastUpdatedAt() const;
    void setLastUpdatedAt(const QDateTime &newLastUpdatedAt);

    int userId() const;
    void setUserId(int newUserId);

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    int userId_ = -1;
    QDateTime lastUpdatedAt_;
};

#endif // SYNCMESSAGEREADSREQUEST_H
