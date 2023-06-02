#include "chatstable.h"

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

    if (!executeQuery(getChatsQuery, ErrorImportance::Critical)) {
        return QList<Chat>{};
    }
    QList<Chat> chats;
    while (getChatsQuery.next()) {
        chats.append(Chat::fromSqlRecord(getChatsQuery.record()));
    }
    return chats;
}

int ChatsTable::addChat(const Chat &chat)
{
    const QString query = readFullFile("./.sql/chats/add_chat.sql");

    QSqlQuery addChatQuery;
    addChatQuery.prepare(query);
    addChatQuery.bindValue(":name", chat.name());
    addChatQuery.bindValue(":description", chat.description());
    addChatQuery.bindValue(":type", Chat::typeToString(chat.type()));

    return (executeQuery(addChatQuery, ErrorImportance::Critical) ? addChatQuery.lastInsertId().toInt() : -1);
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
