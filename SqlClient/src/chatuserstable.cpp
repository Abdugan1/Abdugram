#include "chatuserstable.h"

#include <sql_common/data_structures/chatuser.h>
#include <sql_common/functions.h>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

bool ChatUsersTable::addUserToChat(const ChatUser &chatUser, int chatId)
{
    const QString query = readFullFile("./.sql/chat_users/add_user_to_chat.sql");

    QSqlQuery addUserToChatQuery;
    addUserToChatQuery.prepare(query);
    addUserToChatQuery.bindValue(":chat_id", chatId);
    addUserToChatQuery.bindValue(":user_id", chatUser.userId());
    addUserToChatQuery.bindValue(":role", ChatUser::roleToString(chatUser.role()));
    addUserToChatQuery.bindValue(":joined_at", chatUser.joinedAt());
    addUserToChatQuery.bindValue(":left_at", chatUser.leftAt());

    return executeQuery(addUserToChatQuery, ErrorImportance::Critical);
}
