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
    *stream >> chat_ >> chatUsers_;
}

void CreateChatReply::writeBodyData(DataStream *stream) const
{
    *stream << chat_ << chatUsers_;
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
