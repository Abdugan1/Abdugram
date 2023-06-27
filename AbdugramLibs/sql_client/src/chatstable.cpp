#include "chatstable.h"

#include <sql_common/functions.h>
#include <sql_common/data_structures/user.h>
#include <sql_common/data_structures/chat.h>

#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

bool ChatsTable::isChatExist(const QString &chatName)
{
    const QString query = "SELECT COUNT(*) FROM chats WHERE name = :chat_name;";

    QSqlQuery isChatExistQuery;
    isChatExistQuery.prepare(query);
    isChatExistQuery.bindValue(":chat_name", chatName);

    if (!executeQuery(isChatExistQuery, ErrorImportance::Critical)) {
        return false;
    }

    isChatExistQuery.first();
    return isChatExistQuery.value(0).toBool();
}

bool ChatsTable::addOrUpdateChat(const Chat &chat)
{
    const QString query = "INSERT OR REPLACE INTO chats(id, name, description, type, created_at, updated_at, deleted_at) "
                          "VALUES(:id, :name, :description, :type, :created_at, :updated_at, :deleted_at);";

    QSqlQuery addChatQuery;
    addChatQuery.prepare(query);
    addChatQuery.bindValue(":id", chat.id());
    addChatQuery.bindValue(":name", chat.name());
    addChatQuery.bindValue(":description", chat.description());
    addChatQuery.bindValue(":type", Chat::typeToString(chat.type()));
    addChatQuery.bindValue(":created_at", chat.createdAt());
    addChatQuery.bindValue(":updated_at", chat.updatedAt());
    addChatQuery.bindValue(":deleted_at", chat.deletedAt());

    return executeQuery(addChatQuery, ErrorImportance::Critical);
}

Chat ChatsTable::getChatById(int chatId)
{
    const QString query = "SELECT * FROM chats WHERE id = :id;";

    QSqlQuery getChatByIdQuery;
    getChatByIdQuery.prepare(query);
    getChatByIdQuery.bindValue(":id", chatId);

    if (!executeQuery(getChatByIdQuery, ErrorImportance::Critical))
        return Chat{};

    getChatByIdQuery.first();
    return Chat::fromSqlRecord(getChatByIdQuery.record());
}

QList<Chat> ChatsTable::getAllChats()
{
    const QString query = "SELECT * FROM chats;";

    QSqlQuery getAllChatsQuery{query};
    getAllChatsQuery.setForwardOnly(true);

    if (!executeQuery(getAllChatsQuery, ErrorImportance::Critical)) {
        return QList<Chat>{};
    }


    QList<Chat> chats;

    int size = 0;
    while (getAllChatsQuery.next()) {
        size++;
        chats.append(Chat::fromSqlRecord(getAllChatsQuery.record()));
    }
    qDebug() << "size:" << size;

    return chats;
}
