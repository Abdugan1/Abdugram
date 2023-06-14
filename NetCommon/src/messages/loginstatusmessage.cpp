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
    *stream >> success_ >> user_;
}

void LoginStatusMessage::writeBodyData(DataStream *stream) const
{
    *stream << success_ << user_;
}

User LoginStatusMessage::user() const
{
    return user_;
}

void LoginStatusMessage::setUser(const User &newUser)
{
    user_ = newUser;
}
