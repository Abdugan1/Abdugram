#include "chatuserstable.h"

#include <sql_common/data_structures/chatuser.h>
#include <sql_common/functions.h>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

bool ChatUsersTable::addOrUpdateChatUser(const ChatUser &chatUser)
{
    const QString query = "INSERT OR REPLACE INTO chat_users(chat_id, user_id, role, joined_at, left_at, updated_at) "
                          "VALUES (:chat_id, :user_id, :role, :joined_at, :left_at, :updated_at);";

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
