#include "messagereadstable.h"
#include "sqlquery.h"

#include <sql_common/functions.h>

#include <sql_common/data_structures/messagereads.h>

#include <QVariant>

bool MessageReadsTable::addOrUpdateMessageRead(const MessageRead &messageRead)
{
    SqlQuery query;
    query.prepare("INSERT INTO message_reads(message_id, user_id, read_at, created_at, updated_at) "
                  "VALUES(:message_id, :user_id, :read_at, :created_at, :updated_at) "
                  "ON CONFLICT(user_id, message_id) DO UPDATE SET "
                  "     message_id = excluded.message_id, "
                  "     user_id = excluded.user_id, "
                  "     read_at = excluded.read_at, "
                  "     created_at = excluded.created_at, "
                  "     updated_at = excluded.updated_at;");

    query.bindValue(":message_id", messageRead.messageId());
    query.bindValue(":user_id",    messageRead.userId());
    query.bindValue(":read_at",    messageRead.readTime());
    query.bindValue(":created_at", messageRead.createdAt());
    query.bindValue(":updated_at", messageRead.updatedAt());

    return executeQuery(query, ErrorImportance::Warning);
}

MessageReadsTable::MessageReadsTable()
{

}
