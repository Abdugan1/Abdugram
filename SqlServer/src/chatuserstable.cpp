#include "chatuserstable.h"

#include <sql_common/functions.h>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

bool ChatUsersTable::addUserToChat(int chatId, int userId, ChatUser::Role role)
{
    const QString query = readFullFile("./.sql/chat_users/add_user_to_chat.sql");

    QSqlQuery addUserToChatQuery;
    addUserToChatQuery.prepare(query);
    addUserToChatQuery.bindValue(":chat_id", chatId);
    addUserToChatQuery.bindValue(":user_id", userId);
    addUserToChatQuery.bindValue(":role", ChatUser::roleToString(role));

    return executeQuery(addUserToChatQuery, ErrorImportance::Critical);
}

bool ChatUsersTable::addUsersToChat(int chatId, QList<ChatUser> chatUsers)
{
    for (const auto &chatUser : chatUsers) {
        if (!addUserToChat(chatId, chatUser.userId(), chatUser.role()))
            return false;
    }
    return true;
}

ChatUser ChatUsersTable::getChatUser(int chatId, int userId)
{
    const QString query = readFullFile("./.sql/chat_users/get_chat_user.sql");

    QSqlQuery getChatUserQuery;
    getChatUserQuery.prepare(query);
    getChatUserQuery.bindValue(":chat_id", chatId);
    getChatUserQuery.bindValue(":user_id", userId);

    if (!executeQuery(getChatUserQuery, ErrorImportance::Critical)) {
        return ChatUser{};
    }

    if (!getChatUserQuery.next()) {
        qWarning() << "There is no user with user_id =" << userId << " and chat_id=" << chatId;
        return ChatUser{};
    }

    return ChatUser::fromSqlRecord(getChatUserQuery.record());
}

QList<ChatUser> ChatUsersTable::getChatUsers(int chatId)
{
    const QString query = readFullFile("./.sql/chat_users/get_chat_users.sql");

    QSqlQuery getChatUsersQuery;
    getChatUsersQuery.prepare(query);
    getChatUsersQuery.setForwardOnly(true);
    getChatUsersQuery.bindValue(":chat_id", chatId);

    if (!executeQuery(getChatUsersQuery, ErrorImportance::Critical)) {
        return QList<ChatUser>{};
    }

    QList<ChatUser> chatUsers;
    while (getChatUsersQuery.next()) {
        chatUsers.append(ChatUser::fromSqlRecord(getChatUsersQuery.record()));
    }

    return chatUsers;
}

QList<ChatUser> ChatUsersTable::getUnsyncChatUsers(int userId, int chatId, const QDateTime &lastUpdatedAt)
{
    const QString query = readFullFile("./.sql/chat_users/get_unsync_chat_users.sql");

    QSqlQuery getUnsyncChatUsersQuery;
    getUnsyncChatUsersQuery.setForwardOnly(true);
    getUnsyncChatUsersQuery.prepare(query);
    getUnsyncChatUsersQuery.bindValue(":user_id", userId);
    getUnsyncChatUsersQuery.bindValue(":chat_id", chatId);
    getUnsyncChatUsersQuery.bindValue(":last_updated_at", lastUpdatedAt);

    if (!executeQuery(getUnsyncChatUsersQuery, ErrorImportance::Critical)) {
        return QList<ChatUser>{};
    }

    QList<ChatUser> unsyncChatUsers;

    while (getUnsyncChatUsersQuery.next()) {
        unsyncChatUsers.append(ChatUser::fromSqlRecord(getUnsyncChatUsersQuery.record()));
    }

    return unsyncChatUsers;
}
