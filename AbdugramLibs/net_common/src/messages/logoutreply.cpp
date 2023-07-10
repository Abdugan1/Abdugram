#include "messages/logoutreply.h"
#include "messages/messagevisitor.h"

LogoutReply::LogoutReply()
    : AbduMessage{Type::LogoutReply}
{

}

void LogoutReply::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void LogoutReply::getBodyData(DataStream *stream)
{

}

void LogoutReply::writeBodyData(DataStream *stream) const
{

}
