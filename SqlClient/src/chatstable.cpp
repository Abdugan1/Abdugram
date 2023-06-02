#include "chatstable.h"

#include <sql_common/functions.h>
#include <sql_common/data_structures/user.h>
#include <sql_common/data_structures/chat.h>

#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

bool ChatsTable::isChatExist(const QString &chatName)
{
    const QString query = readFullFile("./.sql/chats/is_chat_exist.sql");
    QSqlQuery isChatExistQuery;
    isChatExistQuery.prepare(query);
    isChatExistQuery.bindValue(":chat_name", chatName);

    if (!executeQuery(isChatExistQuery, ErrorImportance::Critical)) {
        return false;
    }

    isChatExistQuery.first();
    return isChatExistQuery.value(0).toBool();
}

bool ChatsTable::addChat(const Chat &chat)
{
    const QString query = readFullFile("./.sql/chats/add_chat.sql");

    QSqlQuery addChatQuery;
    addChatQuery.prepare(query);
    addChatQuery.bindValue(":name", chat.name());
    addChatQuery.bindValue(":description", chat.description());
    addChatQuery.bindValue(":type", Chat::typeToString(chat.type()));

    return executeQuery(addChatQuery, ErrorImportance::Critical);
}
