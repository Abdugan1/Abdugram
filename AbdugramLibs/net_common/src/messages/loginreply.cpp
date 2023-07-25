#include "messages/loginreply.h"
#include "messages/messagevisitor.h"

#include <QDebug>

LoginReply::LoginReply()
    : AbduMessage{Type::LoginReply}
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
    *stream >> success_ >> userId_;
}

void LoginReply::writeBodyData(DataStream *stream) const
{
    *stream << success_ << userId_;
}

int LoginReply::userId() const
{
    return userId_;
}

void LoginReply::setUserId(int newUserId)
{
    userId_ = newUserId;
}
