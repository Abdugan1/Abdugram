#include "chatsview.h"

#include "data_structures/chatitem.h"
#include "sqlquery.h"

#include <sql_common/functions.h>

#include <QSqlRecord>
#include <QVariant>

QList<ChatViewItem> ChatsView::getChatViews()
{
    SqlQuery query{"SELECT * FROM chats_view;"};
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
    query.prepare("SELECT * FROM chats_view WHERE chat_name LIKE :chat_name");
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
