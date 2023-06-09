#include "messages/createchatmessage.h"
#include "messages/messagevisitor.h"

#include <sql_common/data_structures/chatuser.h>

#include <QDebug>

CreateChatMessage::CreateChatMessage()
    : AbduMessage{Type::CreateChat}
{

}

void CreateChatMessage::accept(MessageVisitor *visitor) const
{
    visitor->visit(*this);
}

void CreateChatMessage::getBodyData(DataStream *stream)
{
    *stream >> chat_ >> chatUsers_;
}

void CreateChatMessage::writeBodyData(DataStream *stream) const
{
    *stream << chat_ << chatUsers_;
}

QList<ChatUser> CreateChatMessage::chatUsers() const
{
    return chatUsers_;
}

void CreateChatMessage::setChatUsers(const QList<ChatUser> &newChatUsers)
{
    chatUsers_ = newChatUsers;
}

Chat CreateChatMessage::chat() const
{
    return chat_;
}

void CreateChatMessage::setChat(const Chat &newChat)
{
    chat_ = newChat;
}
