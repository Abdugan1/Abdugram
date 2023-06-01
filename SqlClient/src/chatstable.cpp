#include "chatstable.h"

#include <sql_common/functions.h>
#include <sql_common/data_structures/user.h>

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

    if (!isChatExistQuery.exec() || !isChatExistQuery.first()) {
        qCritical() << "Couldn't execute query:" << isChatExistQuery.executedQuery()
                    << "error:" << isChatExistQuery.lastError().text();
        return false;
    }

    return isChatExistQuery.value(0).toBool();
}

void ChatsTable::addPrivateChat(int chatId, const User &user1, const User &user2)
{

}
