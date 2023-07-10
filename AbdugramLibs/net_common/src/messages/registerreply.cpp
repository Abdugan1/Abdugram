#include "messages/registerreply.h"
#include "messages/messagevisitor.h"

RegisterReply::RegisterReply()
    : AbduMessage{Type::RegisterReply}
{

}


bool RegisterReply::success() const
{
    return success_;
}

void RegisterReply::setSuccess(bool newSuccess)
{
    success_ = newSuccess;
}

User RegisterReply::user() const
{
    return user_;
}

void RegisterReply::setUser(const User &newUser)
{
    user_ = newUser;
}

void RegisterReply::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void RegisterReply::getBodyData(DataStream *stream)
{
    *stream >> success_ >> user_;
}

void RegisterReply::writeBodyData(DataStream *stream) const
{
    *stream << success_ << user_;
}
