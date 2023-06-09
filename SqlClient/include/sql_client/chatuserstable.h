#ifndef CHATUSERSTABLE_H
#define CHATUSERSTABLE_H

#include "SqlClient_global.h"

#include <QString>

class ChatUser;

class SQLCLIENT_EXPORT ChatUsersTable
{
public:
    static bool addUserToChat(const ChatUser &chatUser, int chatId);
private:
    explicit ChatUsersTable() = default;
};

#endif // CHATUSERSTABLE_H
