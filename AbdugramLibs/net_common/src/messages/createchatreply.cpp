#include "messages/createchatreply.h"
#include "messages/messagevisitor.h"

CreateChatReply::CreateChatReply()
    : AbduMessage{Type::CreateChatResult}
{
}

void CreateChatReply::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void CreateChatReply::getBodyData(DataStream *stream)
{
    *stream >> chat_ >> users_ >> chatUsers_;
}

void CreateChatReply::writeBodyData(DataStream *stream) const
{
    *stream << chat_ << users_ << chatUsers_;
}

QList<User> CreateChatReply::users() const
{
    return users_;
}

void CreateChatReply::setUsers(const QList<User> &newUsers)
{
    users_ = newUsers;
}

QList<ChatUser> CreateChatReply::chatUsers() const
{
    return chatUsers_;
}

void CreateChatReply::setChatUsers(const QList<ChatUser> &newChatUsers)
{
    chatUsers_ = newChatUsers;
}

Chat CreateChatReply::chat() const
{
    return chat_;
}

void CreateChatReply::setChat(const Chat &newChat)
{
    chat_ = newChat;
}
