#include "messagestable.h"

#include <sql_common/data_structures/message.h>
#include <sql_common/functions.h>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

int MessagesTable::lastInsertedId_ = -1;

bool MessagesTable::addOrUpdateMessage(const Message &message)
{
    const QString query = readFullFile("./.sql/messages/add_or_update_message.sql");

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

    const bool success = executeQuery(addMessageQuery, ErrorImportance::Critical);

    lastInsertedId_ = addMessageQuery.lastInsertId().toInt();
    return success;
}

QList<Message> MessagesTable::getMessagesFromChat(int chatId)
{
    const QString query = readFullFile("./.sql/messages/get_messages_from_chat.sql");

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
