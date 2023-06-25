#ifndef CHATUSERSTABLE_H
#define CHATUSERSTABLE_H

#include "SqlServer_global.h"

#include <QString>

#include <sql_common/data_structures/chatuser.h>

class SQLSERVER_EXPORT ChatUsersTable
{
public:
    static bool addUserToChat(int chatId, int userId, ChatUser::Role role);

    //! In chat users parameter, we only need user id and user role in chat
    static bool addUsersToChat(int chatId, QList<ChatUser> chatUsers);

    static ChatUser getChatUser(int chatId, int userId);

    static QList<ChatUser> getChatUsers(int chatId);

    static QList<ChatUser> getUnsyncChatUsers(int userId, int chatId, const QDateTime &lastUpdatedAt);

private:
    explicit ChatUsersTable() = default;

};

#endif // CHATUSERSTABLE_H
