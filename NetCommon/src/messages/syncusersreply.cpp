#include "messages/syncusersreply.h"
#include "messages/messagevisitor.h"

#include <sql_common/data_structures/user.h>

SyncUsersReply::SyncUsersReply()
    : AbduMessage{Type::SyncUsersReply}
{

}

void SyncUsersReply::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void SyncUsersReply::getBodyData(DataStream *stream)
{
    *stream >> users_;
}

void SyncUsersReply::writeBodyData(DataStream *stream) const
{
    *stream << users_;
}

QList<User> SyncUsersReply::users() const
{
    return users_;
}

void SyncUsersReply::setUsers(const QList<User> &newUsers)
{
    users_ = newUsers;
}
