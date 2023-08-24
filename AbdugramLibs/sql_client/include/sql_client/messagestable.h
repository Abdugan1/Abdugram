#ifndef MESSAGESTABLE_H
#define MESSAGESTABLE_H

#include "SqlClient_global.h"

class Message;

class SQLCLIENT_EXPORT MessagesTable
{
public:
    static bool addOrUpdateMessage(const Message &message);

    static Message getMessageById(int chatId);

    static QList<Message> getMessagesFromChat(int chatId);

    static bool updateMessage(const Message &message);

    static int lastInsertedId();

private:
    explicit MessagesTable() = default;

    static int lastInsertedId_;
};

#endif // MESSAGESTABLE_H
