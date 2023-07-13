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

int RegisterReply::userId() const
{
    return userId_;
}

void RegisterReply::setUserId(int newUserId)
{
    userId_ = newUserId;
}

void RegisterReply::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void RegisterReply::getBodyData(DataStream *stream)
{
    *stream >> success_ >> userId_;
}

void RegisterReply::writeBodyData(DataStream *stream) const
{
    *stream << success_ << userId_;
}
