#ifndef SEARCHUSERSREPLY_H
#define SEARCHUSERSREPLY_H

#include "abdumessage.h"

#include <sql_common/data_structures/user.h>

class NETCOMMON_EXPORT SearchUsersReply : public AbduMessage
{
public:
    explicit SearchUsersReply();

    void accept(MessageVisitor *visitor) const override;

    QList<User> users() const;
    void setUsers(const QList<User> &newUsers);

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    QList<User> users_;
};

#endif // SEARCHUSERSREPLY_H
