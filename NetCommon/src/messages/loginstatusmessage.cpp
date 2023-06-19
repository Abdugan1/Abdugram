#include "messages/loginstatusmessage.h"
#include "messages/messagevisitor.h"

LoginStatusMessage::LoginStatusMessage()
    : AbduMessage{Type::LoginStatus}
{

}

bool LoginStatusMessage::success() const
{
    return success_;
}

void LoginStatusMessage::setSuccess(bool newSuccess)
{
    success_ = newSuccess;
}

void LoginStatusMessage::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void LoginStatusMessage::getBodyData(DataStream *stream)
{
    *stream >> success_ >> userId_;
}

void LoginStatusMessage::writeBodyData(DataStream *stream) const
{
    *stream << success_ << userId_;
}

int LoginStatusMessage::userId() const
{
    return userId_;
}

void LoginStatusMessage::setUserId(int newUserId)
{
    userId_ = newUserId;
}
