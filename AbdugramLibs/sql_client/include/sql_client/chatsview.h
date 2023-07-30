#ifndef CHATSVIEW_H
#define CHATSVIEW_H

class SqlQuery;

#include <QList>

class ChatViewItem;

class ChatsView
{
public:
    static QList<ChatViewItem> getChatViews();
    
    static QList<ChatViewItem> getChatViewsByLikeSearch(const QString &likeSearch);

private:
    explicit ChatsView();
};

#endif // CHATSVIEW_H
