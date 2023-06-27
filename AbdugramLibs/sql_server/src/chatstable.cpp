#include "chatstable.h"

#include <sql_common/functions.h>
#include <sql_common/data_structures/chat.h>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

int ChatsTable::lastInsertedId_ = -1;

QList<Chat> ChatsTable::getNewChatsWhereUserIsParticipiant(const QString &username, const QDateTime &lastUpdate)
{
    const QString query = "SELECT * FROM chats "
                          "JOIN participants ON chats.id = participants.chat_id "
                          "JOIN users ON participants.user_id = users.id "
                          "WHERE users.username = :username AND chats.updated_at > :last_update;";

    QSqlQuery getChatsQuery;
    getChatsQuery.setForwardOnly(true);
    getChatsQuery.prepare(query);
    getChatsQuery.bindValue(":username", username);
    getChatsQuery.bindValue(":last_update", lastUpdate);

    if (!executeQuery(getChatsQuery, ErrorImportance::Critical)) {
        return QList<Chat>{};
    }
    QList<Chat> chats;
    while (getChatsQuery.next()) {
        chats.append(Chat::fromSqlRecord(getChatsQuery.record()));
    }
    return chats;
}

bool ChatsTable::addChat(const Chat &chat)
{
    const QString query = "INSERT INTO chats(name, description, type) "
                          "VALUES(:name, :description, :type);";

    QSqlQuery addChatQuery;
    addChatQuery.prepare(query);
    addChatQuery.bindValue(":name", chat.name());
    addChatQuery.bindValue(":description", chat.description());
    addChatQuery.bindValue(":type", Chat::typeToString(chat.type()));

    const bool success = executeQuery(addChatQuery, ErrorImportance::Critical);

    lastInsertedId_ = addChatQuery.lastInsertId().toInt();
    return success;
}

Chat ChatsTable::getChatById(int chatId)
{
    const QString query = "SELECT * FROM chats WHERE id = :chat_id;";

    QSqlQuery getChatByIdQuery;
    getChatByIdQuery.prepare(query);
    getChatByIdQuery.bindValue(":chat_id", chatId);

    if (!executeQuery(getChatByIdQuery, ErrorImportance::Critical)) {
        return Chat{};
    }

    getChatByIdQuery.first();
    return Chat::fromSqlRecord(getChatByIdQuery.record());
}

QList<Chat> ChatsTable::getUnsyncChats(int userId, const QDateTime &lastUpdatedAt)
{
    const QString query = "SELECT c.* "
                          "FROM chats c "
                          "JOIN chat_users cu ON c.id = cu.chat_id "
                          "WHERE  cu.user_id = :user_id "
                          "AND c.updated_at >= :last_updated_at;";

    QSqlQuery getUnsyncChatsQuery;
    getUnsyncChatsQuery.setForwardOnly(true);
    getUnsyncChatsQuery.prepare(query);
    getUnsyncChatsQuery.bindValue(":user_id", userId);
    getUnsyncChatsQuery.bindValue(":last_updated_at", lastUpdatedAt);

    if (!executeQuery(getUnsyncChatsQuery, ErrorImportance::Critical)) {
        return QList<Chat>{};
    }

    QList<Chat> unsyncChats;
    while (getUnsyncChatsQuery.next()) {
        unsyncChats.append(Chat::fromSqlRecord(getUnsyncChatsQuery.record()));
    }

    return unsyncChats;
}

int ChatsTable::lastInsertedId()
{
    return lastInsertedId_;
}
