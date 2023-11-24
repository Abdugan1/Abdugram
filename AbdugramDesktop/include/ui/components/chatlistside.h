#ifndef CHATLISTSIDE_H
#define CHATLISTSIDE_H

#include "ui/components/widget.h"

#include <net_common/messages/abdumessage.h>

#include "ui/mv/chatitem.h"

class QFrame;

class IconButton;
class SearchLineEdit;
class ChatListView;

class ChatModelItem;
using ChatModelItemPtr = std::shared_ptr<ChatModelItem>;

class ChatListSide : public Widget
{
    Q_OBJECT
public:
    explicit ChatListSide(QWidget *parent = nullptr);

    void clearChatSelection();

signals:
    void drawerRequested();

    void selectionWasChanged(const ChatModelItemPtr &selectedChat);

    void newChatItemAdded(const ChatItemPtr &chatItem);

public slots:
    void setToMainModelAndSelectChat(int chatId);

private:
    void setupUi();

private:
    IconButton     *drawerButton_ = nullptr;
    SearchLineEdit *searchLineEdit_ = nullptr;
    ChatListView   *chatListView_   = nullptr;
};

#endif // CHATLISTSIDE_H
