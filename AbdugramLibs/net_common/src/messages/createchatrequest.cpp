#include "messages/createchatrequest.h"
#include "messages/messagevisitor.h"

#include <sql_common/data_structures/chatuser.h>

#include <QDebug>

CreateChatRequest::CreateChatRequest()
    : AbduMessage{Type::CreateChat}
{

}

void CreateChatRequest::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void CreateChatRequest::getBodyData(DataStream *stream)
{
    *stream >> chat_ >> chatUsers_;
}

void CreateChatRequest::writeBodyData(DataStream *stream) const
{
    *stream << chat_ << chatUsers_;
}

QList<ChatUser> CreateChatRequest::chatUsers() const
{
    return chatUsers_;
}

void CreateChatRequest::setChatUsers(const QList<ChatUser> &newChatUsers)
{
    chatUsers_ = newChatUsers;
}

Chat CreateChatRequest::chat() const
{
    return chat_;
}

void CreateChatRequest::setChat(const Chat &newChat)
{
    chat_ = newChat;
}
