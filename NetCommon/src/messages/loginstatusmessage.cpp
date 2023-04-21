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
    *stream >> success_;
}

void LoginStatusMessage::writeBodyData(DataStream *stream) const
{
    *stream << success_;
}
