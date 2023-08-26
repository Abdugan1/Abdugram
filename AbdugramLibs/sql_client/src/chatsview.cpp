#include "chatsview.h"
#include "databaseclient.h".h"

#include "data_structures/chatitem.h"
#include "sqlquery.h"

#include <sql_common/functions.h>

#include <QSqlRecord>
#include <QVariant>

QList<ChatViewItem> ChatsView::getChatViews()
{
    SqlQuery query{"SELECT * FROM chats_view;"};
    query.prepare("SELECT chats.id AS chat_id, chats.name AS chat_name, chats.picture_url AS picture_url, chats.type AS chat_type, messages.text AS last_message, messages.created_at AS message_date, (SELECT COUNT(*) "
                  "FROM messages m "
                  "WHERE is_read = false AND chat_id = chats.id AND sender_id != :own_id) as unread_message_count "
                  "FROM chats "
                  "LEFT JOIN messages ON chats.id = messages.chat_id "
                  "GROUP BY chats.id "
                  "ORDER BY MAX(messages.created_at) DESC;");
    query.bindValue(":own_id", database()->ownId());
    executeQuery(query, ErrorImportance::Warning);
    
    QList<ChatViewItem> chatViews;
    while (query.next()) {
        chatViews.append(ChatViewItem::fromSqlRecord(query.record()));
    }
    return chatViews;
}

QList<ChatViewItem> ChatsView::getChatViewsByLikeSearch(const QString &likeSearch)
{
    SqlQuery query;
    query.prepare("SELECT chats.id AS chat_id, chats.name AS chat_name, chats.picture_url AS picture_url, chats.type AS chat_type, messages.text AS last_message, messages.created_at AS message_date, (SELECT COUNT(*) "
                  "FROM messages m "
                  "WHERE is_read = false AND chat_id = chats.id AND sender_id != :own_id) as unread_message_count "
                  "FROM chats "
                  "LEFT JOIN messages ON chats.id = messages.chat_id "
                  "WHERE chat_name LIKE :chat_name "
                  "GROUP BY chats.id "
                  "ORDER BY MAX(messages.created_at) DESC;");
    query.bindValue(":own_id", database()->ownId());
    query.bindValue(":chat_name", likeSearch);
    executeQuery(query, ErrorImportance::Warning);
    
    QList<ChatViewItem> chatViews;
    while (query.next()) {
        chatViews.append(ChatViewItem::fromSqlRecord(query.record()));
    }

    return chatViews;
}

ChatsView::ChatsView()
{

}
