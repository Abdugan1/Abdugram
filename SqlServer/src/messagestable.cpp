#include "messagestable.h"

#include <sql_common/data_structures/message.h>
#include <sql_common/functions.h>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

int MessagesTable::lastInsertedId_ = -1;

bool MessagesTable::addMessage(const Message &message)
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

int MessagesTable::lastInsertedId()
{
    return lastInsertedId_;
}
