#include "messages/logoutrequest.h"
#include "messages/messagevisitor.h"

LogoutRequest::LogoutRequest()
    : AbduMessage{Type::LogoutRequest}
{

}

void LogoutRequest::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void LogoutRequest::getBodyData(DataStream *stream)
{
}

void LogoutRequest::writeBodyData(DataStream *stream) const
{
}
