#ifndef CHATSTABLE_H
#define CHATSTABLE_H

#include "SqlClient_global.h"

#include "chatuserstable.h"

class User;
class Chat;

class SQLCLIENT_EXPORT ChatsTable
{
public:
    static bool isChatExist(const QString &chatName);

    static bool addChat(const Chat &chat);
};

#endif // CHATSTABLE_H
