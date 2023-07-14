#ifndef CHATLISTVIEW_H
#define CHATLISTVIEW_H

#include <QListView>

#include "chatitem.h"

class ChatListModel;
class ChatListDelegate;

class User;
class Chat;

class ChatListView : public QListView
{
    Q_OBJECT
public:
    explicit ChatListView(QWidget *parent = nullptr);

    void addNewChatItemToMainModel(const ChatItemPtr &chatItem);

signals:
    void selectionWasChangedByUser(const ChatItemPtr &selectedChat);

    void highlightColorChanged();

public slots:
    void setMainModel();
    void setTemporaryModel(const QList<User> &foundUserList);

protected slots:
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) override;

private slots:
    void initMainModel();
    void updateMainModel();

private:
    ChatListModel *mainModel_ = nullptr;
    ChatListModel *tempModel_ = nullptr;

    ChatListDelegate *delegate_  = nullptr;

    bool selectionByUser_ = true;
};

#endif // CHATLISTVIEW_H
