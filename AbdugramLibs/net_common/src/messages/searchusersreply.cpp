#include "messages/searchusersreply.h"
#include "messages/messagevisitor.h"

#include <sql_common/data_structures/user.h>

SearchUsersReply::SearchUsersReply()
    : AbduMessage{Type::SearchUsersResult}
{

}

void SearchUsersReply::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

QList<User> SearchUsersReply::users() const
{
    return users_;
}

void SearchUsersReply::setUsers(const QList<User> &newUsers)
{
    users_ = newUsers;
}

void SearchUsersReply::getBodyData(DataStream *stream)
{
    *stream >> users_;
}

void SearchUsersReply::writeBodyData(DataStream *stream) const
{
    *stream << users_;
}
