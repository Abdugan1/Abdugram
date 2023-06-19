#ifndef SYNCCHATSREQUEST_H
#define SYNCCHATSREQUEST_H

#include "abdumessage.h"
#include <QDateTime>

class NETCOMMON_EXPORT SyncChatsRequest : public AbduMessage
{
public:
    explicit SyncChatsRequest();

    int userId() const;
    void setUserId(int newUserId);

    QDateTime lastUpdate() const;
    void setLastUpdate(const QDateTime &newLastUpdate);

    void accept(MessageVisitor *visitor) const override;

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    int userId_ = -1;
    QDateTime lastUpdate_;

};

#endif // SYNCCHATSREQUEST_H
