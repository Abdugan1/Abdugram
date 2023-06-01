#include "messages/createprivatechatresultmessage.h"
#include "messages/messagevisitor.h"

CreatePrivateChatResultMessage::CreatePrivateChatResultMessage()
    : AbduMessage{Type::CreatePrivateChatResult}
{
}

void CreatePrivateChatResultMessage::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void CreatePrivateChatResultMessage::getBodyData(DataStream *stream)
{
    *stream >> chatId_ >> secondParticipiant_;
}

void CreatePrivateChatResultMessage::writeBodyData(DataStream *stream) const
{
    *stream << chatId_ << secondParticipiant_;
}

User CreatePrivateChatResultMessage::secondParticipiant() const
{
    return secondParticipiant_;
}

void CreatePrivateChatResultMessage::setSecondParticipiant(const User &newSecondParticipiant)
{
    secondParticipiant_ = newSecondParticipiant;
}

int CreatePrivateChatResultMessage::chatId() const
{
    return chatId_;
}

void CreatePrivateChatResultMessage::setChatId(int newChatId)
{
    chatId_ = newChatId;
}
