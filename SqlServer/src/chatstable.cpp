#include "chatstable.h"

#include <sql_common/functions.h>
#include <sql_common/data_structures/chat.h>

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

Chat getChatFromQueryResult(const QSqlRecord &record)
{
    Chat chat;
    chat.setId(record.value("id").toInt());
    chat.setName(record.value("name").toString());
    chat.setCreatedByUserId(record.value("created_by_user_id").toInt());
    return chat;
}

ChatsTable::ChatsTable()
{

}

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
