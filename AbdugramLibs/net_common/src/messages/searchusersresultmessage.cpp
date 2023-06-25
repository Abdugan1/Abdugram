#include "messages/searchusersresultmessage.h"
#include "messages/messagevisitor.h"

#include <sql_common/data_structures/user.h>

SearchUsersResultMessage::SearchUsersResultMessage()
    : AbduMessage{Type::SearchUsersResult}
{

}

void SearchUsersResultMessage::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

QList<User> SearchUsersResultMessage::users() const
{
    return users_;
}

void SearchUsersResultMessage::setUsers(const QList<User> &newUsers)
{
    users_ = newUsers;
}

void SearchUsersResultMessage::getBodyData(DataStream *stream)
{
    *stream >> users_;
}

void SearchUsersResultMessage::writeBodyData(DataStream *stream) const
{
    *stream << users_;
}
