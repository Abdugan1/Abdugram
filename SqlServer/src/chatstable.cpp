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
    const QString query = readFullFile("./.sql/chats/get_new_chats_where_username_is_participiant.sql");

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
    const QString query = readFullFile("./.sql/chats/add_chat.sql");

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
    const QString query = readFullFile("./.sql/chats/get_chat_by_id.sql");

    QSqlQuery getChatByIdQuery;
    getChatByIdQuery.prepare(query);
    getChatByIdQuery.bindValue(":chat_id", chatId);

    if (!executeQuery(getChatByIdQuery, ErrorImportance::Critical)) {
        return Chat{};
    }

    getChatByIdQuery.first();
    return Chat::fromSqlRecord(getChatByIdQuery.record());
}

int ChatsTable::lastInsertedId()
{
    return lastInsertedId_;
}
