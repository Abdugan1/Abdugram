#ifndef MESSAGESTABLE_H
#define MESSAGESTABLE_H

#include "SqlClient_global.h"

class Message;

class SQLCLIENT_EXPORT MessagesTable
{
public:
    static bool addMessage(const Message &message);

    static QList<Message> getMessages(int chatId);

    static int lastInsertedId();

private:
    explicit MessagesTable() = default;

    static int lastInsertedId_;
};

#endif // MESSAGESTABLE_H
