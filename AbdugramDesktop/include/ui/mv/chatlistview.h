#ifndef CHATLISTVIEW_H
#define CHATLISTVIEW_H

#include <QListView>

#include "chatitem.h"

class ChatListModel;
class ChatListDelegate;

class User;
class Chat;

class ChatModelItem;
using ChatModelItemPtr = std::shared_ptr<ChatModelItem>;

class ChatViewItem;

class ChatItem;
class FoundUserItem;

using ChatItemPtr = std::shared_ptr<ChatItem>;
using FoundUserItemPtr = std::shared_ptr<FoundUserItem>;

class ChatListView : public QListView
{
    Q_OBJECT
public:
    explicit ChatListView(QWidget *parent = nullptr);

signals:
    void newChatItemAdded(const ChatItemPtr &chatItem);

    void chatSelected(const ChatModelItemPtr &chat);
    void foundUserSelected(const ChatModelItemPtr &foundUser);

    void highlightColorChanged();

    void localSearchFinished();

public slots:
    void setMainModel();
    void setMainModelSelected(int chatId);

    void addFoundUsers(const QList<User> &foundUsers);

protected slots:
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) override;

private slots:
    void initMainModel();
    void updateMainModel();

    void onLoggedOut();

    void addNewChatToMainModel(const Chat &chat);

    void onChatsFound(const QList<ChatViewItem> &chatViews);  

private:
    ChatListModel *mainModel_ = nullptr;
    ChatListModel *tempModel_ = nullptr;

    ChatListDelegate *delegate_  = nullptr;

    bool selectionByUser_ = true;
};

#endif // CHATLISTVIEW_H
