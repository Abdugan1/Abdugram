#include "messages/loginreply.h"
#include "messages/messagevisitor.h"

LoginReply::LoginReply()
    : AbduMessage{Type::LoginStatus}
{

}

bool LoginReply::success() const
{
    return success_;
}

void LoginReply::setSuccess(bool newSuccess)
{
    success_ = newSuccess;
}

void LoginReply::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void LoginReply::getBodyData(DataStream *stream)
{
    *stream >> success_ >> user_;
}

void LoginReply::writeBodyData(DataStream *stream) const
{
    *stream << success_ << user_;
}

User LoginReply::user() const
{
    return user_;
}

void LoginReply::setUser(const User &newUser)
{
    user_ = newUser;
}
