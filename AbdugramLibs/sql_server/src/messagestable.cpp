#include "messagestable.h"

#include <sql_common/data_structures/message.h>
#include <sql_common/functions.h>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

int MessagesTable::lastInsertedId_ = -1;

bool MessagesTable::addMessage(const Message &message)
{
    const QString query = "INSERT INTO messages(chat_id, sender_id, reply_to_id, text) "
                          "VALUES(:chat_id, :sender_id, :reply_to_id, :text);";

    QSqlQuery addMessageQuery;
    addMessageQuery.prepare(query);
    addMessageQuery.bindValue(":chat_id", message.chatId());
    addMessageQuery.bindValue(":sender_id", message.senderId());

    if (message.replyToId() != -1)
        addMessageQuery.bindValue(":reply_to_id", message.replyToId());

    addMessageQuery.bindValue(":text", message.text());

    const bool success = executeQuery(addMessageQuery, ErrorImportance::Critical);

    lastInsertedId_ = addMessageQuery.lastInsertId().toInt();
    return success;
}

Message MessagesTable::getMessageById(int id)
{
    const QString query = "SELECT * FROM messages WHERE id = :id;";

    QSqlQuery getMessageByIdQuery;
    getMessageByIdQuery.prepare(query);
    getMessageByIdQuery.bindValue(":id", id);

    if (!executeQuery(getMessageByIdQuery, ErrorImportance::Critical))
        return Message{};

    getMessageByIdQuery.first();
    return Message::fromSqlRecord(getMessageByIdQuery.record());
}

QList<Message> MessagesTable::getUnsyncMessages(int userId, const QDateTime &lastUpdatedAt)
{
    const QString query = "SELECT m.* "
                          "FROM messages m "
                          "WHERE m.chat_id IN ( "
                          "SELECT cu.chat_id "
                          "FROM chat_users cu "
                          "WHERE cu.user_id = :user_id "
                          ") "
                          "AND m.updated_at >= :last_updated_at;";

    QSqlQuery getUnsyncMessagesQuery;
    getUnsyncMessagesQuery.setForwardOnly(true);
    getUnsyncMessagesQuery.prepare(query);
    getUnsyncMessagesQuery.bindValue(":user_id", userId);
    getUnsyncMessagesQuery.bindValue(":last_updated_at", lastUpdatedAt);

    if (!executeQuery(getUnsyncMessagesQuery, ErrorImportance::Critical)) {
        return QList<Message>{};
    }

    QList<Message> unsyncMessages;
    while (getUnsyncMessagesQuery.next()) {
        unsyncMessages.append(Message::fromSqlRecord(getUnsyncMessagesQuery.record()));
    }

    return unsyncMessages;
}

int MessagesTable::lastInsertedId()
{
    return lastInsertedId_;
}
