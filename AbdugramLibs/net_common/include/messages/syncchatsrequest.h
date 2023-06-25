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

    QDateTime chatsLastUpdatedAt() const;
    void setChatsLastUpdatedAt(const QDateTime &newLastUpdate);

    void accept(MessageVisitor *visitor) const override;

    QDateTime chatUsersLastUpdatedAt() const;
    void setChatUsersLastUpdatedAt(const QDateTime &newChatUsersLastUpdatedAt);

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    int userId_ = -1;
    QDateTime chatsLastUpdatedAt_;
    QDateTime chatUsersLastUpdatedAt_;

};

#endif // SYNCCHATSREQUEST_H
