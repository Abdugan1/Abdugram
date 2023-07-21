#include "messages/createprivatechatrequest.h"
#include "messages/messagevisitor.h"

CreatePrivateChatRequest::CreatePrivateChatRequest()
    : AbduMessage{Type::CreatePrivateChatRequest}
{

}

void CreatePrivateChatRequest::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void CreatePrivateChatRequest::getBodyData(DataStream *stream)
{
    *stream >> chat_ >> chatUsers_ >> message_;
}

void CreatePrivateChatRequest::writeBodyData(DataStream *stream) const
{
    *stream << chat_ << chatUsers_ << message_;
}

Chat CreatePrivateChatRequest::chat() const
{
    return chat_;
}

void CreatePrivateChatRequest::setChat(const Chat &newChat)
{
    chat_ = newChat;
}

QList<ChatUser> CreatePrivateChatRequest::chatUsers() const
{
    return chatUsers_;
}

void CreatePrivateChatRequest::setChatUsers(const QList<ChatUser> &newChatUsers)
{
    chatUsers_ = newChatUsers;
}

Message CreatePrivateChatRequest::message() const
{
    return message_;
}

void CreatePrivateChatRequest::setMessage(const Message &newMessage)
{
    message_ = newMessage;
}

