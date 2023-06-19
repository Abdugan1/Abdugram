#ifndef SYNCUSERSMESSAGE_H
#define SYNCUSERSMESSAGE_H

#include "abdumessage.h"

#include <QDateTime>

class NETCOMMON_EXPORT SyncUsersMessage : public AbduMessage
{
public:
    explicit SyncUsersMessage();

    void accept(MessageVisitor *visitor) const override;

    int userId() const;
    void setUserId(int newUserId);

    QDateTime lastUpdatedAt() const;
    void setLastUpdatedAt(const QDateTime &newLastUpdatedAt);

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    int userId_ = -1;
    QDateTime lastUpdatedAt_;
};

#endif // SYNCUSERSMESSAGE_H
