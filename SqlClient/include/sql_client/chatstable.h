#ifndef CHATSTABLE_H
#define CHATSTABLE_H

#include "SqlClient_global.h"

#include "chatuserstable.h"

#include <QList>

class QDateTime;

class User;
class Chat;

class SQLCLIENT_EXPORT ChatsTable
{
public:
    static bool isChatExist(const QString &chatName);

    static bool addChat(const Chat &chat);

    static Chat getChatById(int chatId);

    static QList<Chat> getAllChats();

private:
    explicit ChatsTable() = default;
};

#endif // CHATSTABLE_H
