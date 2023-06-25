#include "messagestable.h"

#include <sql_common/data_structures/message.h>
#include <sql_common/functions.h>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

int MessagesTable::lastInsertedId_ = -1;

bool MessagesTable::addOrUpdateMessage(const Message &message)
{
    const QString query = readFullFile("./.sql/messages/add_message.sql");

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
    const QString query = readFullFile("./.sql/messages/get_message_by_id.sql");

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
    const QString query = readFullFile("./.sql/messages/get_unsync_messages.sql");

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
