#include "messages/isusernamefreerequest.h"
#include "messages/messagevisitor.h"

IsUsernameFreeRequest::IsUsernameFreeRequest()
    : AbduMessage{Type::IsUsernameFreeRequest}
{

}

void IsUsernameFreeRequest::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

QString IsUsernameFreeRequest::username() const
{
    return username_;
}

void IsUsernameFreeRequest::setUsername(const QString &newUsername)
{
    username_ = newUsername;
}

void IsUsernameFreeRequest::getBodyData(DataStream *stream)
{
    *stream >> username_;
}

void IsUsernameFreeRequest::writeBodyData(DataStream *stream) const
{
    *stream << username_;
}
