#ifndef SIDEPANEL_H
#define SIDEPANEL_H

#include "ui/components/widget.h"

#include <net_common/messages/abdumessage.h>

#include "ui/mv/chatitem.h"

class QFrame;

class IconButton;
class SearchLineEdit;
class ChatListView;

class ChatModelItem;
using ChatModelItemPtr = std::shared_ptr<ChatModelItem>;

class SidePanel : public QWidget
{
    Q_OBJECT
public:
    explicit SidePanel(QWidget *parent = nullptr);

    void clearChatSelection();

signals:
    void sideMenuRequested();

    void selectionWasChanged(const ChatModelItemPtr &selectedChat);

    void newChatItemAdded(const ChatItemPtr &chatItem);

public slots:
    void setToMainModelAndSelectChat(int chatId);

private:
    void setupUi();

private:
    IconButton    *sideMenuButton_ = nullptr;
    SearchLineEdit *searchLineEdit_ = nullptr;
    ChatListView   *chatListView_   = nullptr;
};

#endif // SIDEPANEL_H
