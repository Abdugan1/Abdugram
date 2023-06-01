#include "messages/createprivatechatmessage.h"
#include "messages/messagevisitor.h"

CreatePrivateChatMessage::CreatePrivateChatMessage()
    : AbduMessage{Type::CreatePrivateChat}
{

}

void CreatePrivateChatMessage::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void CreatePrivateChatMessage::getBodyData(DataStream *stream)
{
    *stream >> user1Id_ >> user2Id_;
}

void CreatePrivateChatMessage::writeBodyData(DataStream *stream) const
{
    *stream << user1Id_ << user2Id_;
}

int CreatePrivateChatMessage::user1Id() const
{
    return user1Id_;
}

void CreatePrivateChatMessage::setUser1Id(int newUser1)
{
    user1Id_ = newUser1;
}

int CreatePrivateChatMessage::user2Id() const
{
    return user2Id_;
}

void CreatePrivateChatMessage::setUser2Id(int newUser2)
{
    user2Id_ = newUser2;
}
