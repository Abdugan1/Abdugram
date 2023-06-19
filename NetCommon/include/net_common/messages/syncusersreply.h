#ifndef SYNCUSERSREPLY_H
#define SYNCUSERSREPLY_H

#include "abdumessage.h"

class User;

class NETCOMMON_EXPORT SyncUsersReply : public AbduMessage
{
public:
    explicit SyncUsersReply();

    void accept(MessageVisitor *visitor) const override;

    QList<User> users() const;
    void setUsers(const QList<User> &newUsers);

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    QList<User> users_;
};

#endif // SYNCUSERSREPLY_H
