#include "messages/isusernamefreereply.h"
#include "messages/messagevisitor.h"

IsUsernameFreeReply::IsUsernameFreeReply()
    : AbduMessage{Type::IsUsernameFreeReply}
{

}

void IsUsernameFreeReply::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void IsUsernameFreeReply::getBodyData(DataStream *stream)
{
    *stream >> isFree_;
}

void IsUsernameFreeReply::writeBodyData(DataStream *stream) const
{
    *stream << isFree_;
}

bool IsUsernameFreeReply::isFree() const
{
    return isFree_;
}

void IsUsernameFreeReply::setIsFree(bool newIsFree)
{
    isFree_ = newIsFree;
}
