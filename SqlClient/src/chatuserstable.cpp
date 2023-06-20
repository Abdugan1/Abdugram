#include "chatuserstable.h"

#include <sql_common/data_structures/chatuser.h>
#include <sql_common/functions.h>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

bool ChatUsersTable::addOrUpdateChatUser(const ChatUser &chatUser)
{
    const QString query = readFullFile("./.sql/chat_users/add_or_update_chat_user.sql");

    QSqlQuery addUserToChatQuery;
    addUserToChatQuery.prepare(query);
    addUserToChatQuery.bindValue(":chat_id", chatUser.chatId());
    addUserToChatQuery.bindValue(":user_id", chatUser.userId());
    addUserToChatQuery.bindValue(":role", ChatUser::roleToString(chatUser.role()));
    addUserToChatQuery.bindValue(":joined_at", chatUser.joinedAt());
    addUserToChatQuery.bindValue(":left_at", chatUser.leftAt());
    addUserToChatQuery.bindValue(":updated_at", chatUser.updatedAt());

    return executeQuery(addUserToChatQuery, ErrorImportance::Critical);
}