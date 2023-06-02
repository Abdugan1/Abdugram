#include "messages/createchatresultmessage.h"
#include "messages/messagevisitor.h"

#include <sql_common/data_structures/chatuser.h>

CreateChatResultMessage::CreateChatResultMessage()
    : AbduMessage{Type::CreatePrivateChatResult}
{
}

void CreateChatResultMessage::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void CreateChatResultMessage::getBodyData(DataStream *stream)
{
    *stream >> chat_ >> chatUsers_;
}

void CreateChatResultMessage::writeBodyData(DataStream *stream) const
{
    *stream << chat_ << chatUsers_;
}

QList<ChatUser> CreateChatResultMessage::chatUsers() const
{
    return chatUsers_;
}

void CreateChatResultMessage::setChatUsers(const QList<ChatUser> &newChatUsers)
{
    chatUsers_ = newChatUsers;
}

Chat CreateChatResultMessage::chat() const
{
    return chat_;
}

void CreateChatResultMessage::setChat(const Chat &newChat)
{
    chat_ = newChat;
}
