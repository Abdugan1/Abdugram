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

void RegisterStatusMessage::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void RegisterStatusMessage::getBodyData(DataStream *stream)
{
    *stream >> success_;
}

void RegisterStatusMessage::writeBodyData(DataStream *stream) const
{
    *stream << success_;
}
