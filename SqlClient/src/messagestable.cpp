#include "messagestable.h"

#include <sql_common/data_structures/message.h>
#include <sql_common/functions.h>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

int MessagesTable::lastInsertedId_ = -1;

bool MessagesTable::addMessage(const Message &message)
{
    const QString query = readFullFile("./.sql/messages/add_message.sql");

    QSqlQuery addMessageQuery;
    addMessageQuery.prepare(query);
    addMessageQuery.bindValue(":id", message.id());
    addMessageQuery.bindValue(":chat_id", message.chatId());
    addMessageQuery.bindValue(":sender_id", message.senderId());

    if (message.replyToId() != -1)
        addMessageQuery.bindValue(":reply_to_id", message.replyToId());

    addMessageQuery.bindValue(":text", message.text());
    addMessageQuery.bindValue(":is_edited", message.isEdited());
    addMessageQuery.bindValue(":created_at", message.createdAt());
    addMessageQuery.bindValue(":updated_at", message.updatedAt());

    bool success = executeQuery(addMessageQuery, ErrorImportance::Critical);

    if (success)
        lastInsertedId_ = addMessageQuery.lastInsertId().toInt();

    return success;
}

QList<Message> MessagesTable::getMessages(int chatId)
{
    const QString query = readFullFile("./.sql/messages/get_messages.sql");

    QSqlQuery getMessagesQuery;
    getMessagesQuery.prepare(query);
    getMessagesQuery.bindValue(":chat_id", chatId);

    if (!executeQuery(getMessagesQuery, ErrorImportance::Critical)) {
        return QList<Message>{};
    }

    QList<Message> messages;
    while (getMessagesQuery.next()) {
        messages.append(Message::fromSqlRecord(getMessagesQuery.record()));
    }

    return messages;
}

int MessagesTable::lastInsertedId()
{
    return lastInsertedId_;
}
