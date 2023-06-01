#ifndef CHATSTABLE_H
#define CHATSTABLE_H

#include "SqlClient_global.h"

class User;

class SQLCLIENT_EXPORT ChatsTable
{
public:
    static bool isChatExist(const QString &chatName);

    static void addPrivateChat(int chatId, const User &user1, const User& user2);
};

#endif // CHATSTABLE_H
