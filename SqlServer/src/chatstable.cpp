#include "chatstable.h"
#include "userstable.h"

#include <sql_common/functions.h>
#include <sql_common/data_structures/chat.h>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

QList<Chat> ChatsTable::getNewChatsWhereUserIsParticipiant(const QString &username, const QDateTime &lastUpdate)
{
    const QString query = readFullFile("./.sql/chats/get_new_chats_where_username_is_participiant.sql");

    QSqlQuery getChatsQuery;
    getChatsQuery.setForwardOnly(true);
    getChatsQuery.prepare(query);
    getChatsQuery.bindValue(":username", username);
    getChatsQuery.bindValue(":last_update", lastUpdate);

    if (!getChatsQuery.exec()) {
        qCritical() << "Coudln't execute query:" << getChatsQuery.executedQuery()
                    << "error:" << getChatsQuery.lastError().text();
    }
    QList<Chat> chats;
    while (getChatsQuery.next()) {
        chats.append(getChatFromQueryResult(getChatsQuery.record()));
    }
    return chats;
}

int ChatsTable::createPrivateChat(int user1Id, int user2Id)
{
    // Start transaction
    QSqlDatabase::database().transaction();

    QSqlQuery createPrivateChatQuery;
    if (createPrivateChatQuery.exec(readFullFile("./sql/chats/create_private_chat.sql"))) {
        qCritical() << "Coudln't execute query:" << createPrivateChatQuery.executedQuery()
                    << "error:" << createPrivateChatQuery.lastError().text();
        QSqlDatabase::database().rollback();
        return -1;
    }

    const int autoIncrementedChatId = createPrivateChatQuery.lastInsertId().toInt();

    const QString query = readFullFile("./sql/chat_users/add_user_to_chat.sql");

    QSqlQuery addUserToChatQuery;
    addUserToChatQuery.prepare(query);
    addUserToChatQuery.bindValue(":chat_id", autoIncrementedChatId);
    addUserToChatQuery.bindValue(":role", "admin");

    // Add first user
    addUserToChatQuery.bindValue(":user_id", user1Id);
    if (!addUserToChatQuery.exec()) {
        qCritical() << "Coudln't execute query:" << addUserToChatQuery.executedQuery()
                    << "error:" << addUserToChatQuery.lastError().text();
        QSqlDatabase::database().rollback();
        return -1;
    }

    // Add second user
    addUserToChatQuery.bindValue(":user_id", user2Id);
    if (!addUserToChatQuery.exec()) {
        qCritical() << "Coudln't execute query:" << addUserToChatQuery.executedQuery()
                    << "error:" << addUserToChatQuery.lastError().text();
        QSqlDatabase::database().rollback();
        return -1;
    }

    // Commit transaction
    if (!QSqlDatabase::database().commit()) {
        qCritical() << "Failed to commit transaction:" << QSqlDatabase::database().lastError().text();
        QSqlDatabase::database().rollback();
        return -1;
    }

    return autoIncrementedChatId;
}
