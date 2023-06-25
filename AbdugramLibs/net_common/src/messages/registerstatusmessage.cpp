#include "messages/registerstatusmessage.h"
#include "messages/messagevisitor.h"

RegisterStatusMessage::RegisterStatusMessage()
    : AbduMessage{Type::RegisterStaus}
{

}


bool RegisterStatusMessage::success() const
{
    return success_;
}

void RegisterStatusMessage::setSuccess(bool newSuccess)
{
    success_ = newSuccess;
}

User RegisterStatusMessage::user() const
{
    return user_;
}

void RegisterStatusMessage::setUser(const User &newUser)
{
    user_ = newUser;
}

void RegisterStatusMessage::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void RegisterStatusMessage::getBodyData(DataStream *stream)
{
    *stream >> success_ >> user_;
}

void RegisterStatusMessage::writeBodyData(DataStream *stream) const
{
    *stream << success_ << user_;
}
