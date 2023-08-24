#include "messagestable.h"
#include "sqlquery.h"

#include <sql_common/data_structures/message.h>
#include <sql_common/functions.h>

#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

int MessagesTable::lastInsertedId_ = -1;

bool MessagesTable::addOrUpdateMessage(const Message &message)
{
    const QString query = "INSERT INTO messages(id, chat_id, sender_id, reply_to_id, text, is_edited, is_read, created_at, updated_at)  "
                          "VALUES (:id, :chat_id, :sender_id, :reply_to_id, :text, :is_edited, :is_read, :created_at, :updated_at) "
                          "ON CONFLICT(id) DO UPDATE SET "
                          "     chat_id = excluded.chat_id, "
                          "     sender_id = excluded.sender_id, "
                          "     reply_to_id = excluded.reply_to_id, "
                          "     text = excluded.text, "
                          "     is_edited = excluded.is_edited, "
                          "     is_read = excluded.is_read, "
                          "     created_at = excluded.created_at, "
                          "     updated_at = excluded.updated_at;";

    SqlQuery addMessageQuery;
    addMessageQuery.prepare(query);
    addMessageQuery.bindValue(":id", message.id());
    addMessageQuery.bindValue(":chat_id", message.chatId());
    addMessageQuery.bindValue(":sender_id", message.senderId());

    if (message.replyToId() != -1)
        addMessageQuery.bindValue(":reply_to_id", message.replyToId());

    addMessageQuery.bindValue(":text", message.text());
    addMessageQuery.bindValue(":is_edited", message.isEdited());
    addMessageQuery.bindValue(":is_read", message.isRead());
    addMessageQuery.bindValue(":created_at", message.createdAt());
    addMessageQuery.bindValue(":updated_at", message.updatedAt());

    const bool success = executeQuery(addMessageQuery, ErrorImportance::Critical);

    lastInsertedId_ = addMessageQuery.lastInsertId().toInt();
    return success;
}

Message MessagesTable::getMessageById(int id)
{
    const QString query = "SELECT * FROM messages WHERE id = :id;";

    SqlQuery getMessageByIdQuery;
    getMessageByIdQuery.prepare(query);
    getMessageByIdQuery.bindValue(":id", id);

    if (!executeQuery(getMessageByIdQuery, ErrorImportance::Critical))
        return Message{};

    getMessageByIdQuery.first();
    return Message::fromSqlRecord(getMessageByIdQuery.record());
}

QList<Message> MessagesTable::getMessagesFromChat(int chatId)
{
    const QString query = "SELECT * FROM messages WHERE chat_id = :chat_id;";

    SqlQuery getMessagesQuery;
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

bool MessagesTable::updateMessage(const Message &message)
{
    SqlQuery query;
    query.prepare("UPDATE messages SET text = :text, is_edited = :is_edited, "
                  "is_read = :is_read, updated_at = :updated_at WHERE id = :message_id");
    query.bindValue(":text", message.text());
    query.bindValue(":is_edited", message.isEdited());
    query.bindValue(":is_read", message.isRead());
    query.bindValue(":updated_at", message.updatedAt());
    query.bindValue(":message_id", message.id());

    return executeQuery(query, ErrorImportance::Warning);
}

int MessagesTable::lastInsertedId()
{
    return lastInsertedId_;
}
