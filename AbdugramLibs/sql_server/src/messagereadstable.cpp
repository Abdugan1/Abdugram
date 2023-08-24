#include "messagereadstable.h"
#include <QSqlDatabase>

#include <sql_common/functions.h>
#include <sql_common/data_structures/messagereads.h>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDateTime>
#include <QDebug>

int MessageReadsTable::lastInsertedId_ = -1;

bool MessageReadsTable::addMessageReads(const MessageRead &messageRead)
{
    QSqlQuery query;
    query.prepare("INSERT INTO message_reads(message_id, user_id, read_at, created_at, updated_at)"
                  "VALUES(:message_id, :user_id, :read_at, :created_at, :updated_at)");
    query.bindValue(":user_id", messageRead.userId());
    query.bindValue(":message_id", messageRead.messageId());
    query.bindValue(":read_at", messageRead.readTime());
    query.bindValue(":created_at", messageRead.createdAt());
    query.bindValue(":updated_at", messageRead.updatedAt());

    lastInsertedId_ = query.lastInsertId().toInt();
    return executeQuery(query, ErrorImportance::Warning);
}

QList<MessageRead> MessageReadsTable::getUnsyncMessageReads(int userId, const QDateTime &lastUpdatedAt)
{
    QSqlQuery query;
    query.prepare("SELECT mr.* "
                  "FROM message_reads mr  "
                  "JOIN messages m ON m.id = mr.message_id  "
                  "WHERE m.chat_id IN (  "
                  "     SELECT cu.chat_id  "
                  "     FROM chat_users cu  "
                  "     WHERE cu.user_id = :user_id  "
                  ") "
                  "AND mr.updated_at >= :last_updated_at;");
    query.bindValue(":user_id", userId);
    query.bindValue(":last_updated_at", lastUpdatedAt);

    if (!executeQuery(query, ErrorImportance::Critical))
        return QList<MessageRead>{};

    QList<MessageRead> messageReads;
    while (query.next()) {
        messageReads.append(MessageRead::fromSqlRecord(query.record()));
    }

    return messageReads;
}

MessageReadsTable::MessageReadsTable()
{

}
