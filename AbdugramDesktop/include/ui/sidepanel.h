#ifndef SIDEPANEL_H
#define SIDEPANEL_H

#include <QFrame>

#include <net_common/messages/abdumessage.h>

#include "mv/chatitem.h"

class QFrame;

class ImageButton;
class SearchLineEdit;
class ChatListView;

class ChatModelItem;
using ChatModelItemPtr = std::shared_ptr<ChatModelItem>;

class SidePanel : public QFrame
{
    Q_OBJECT
public:
    explicit SidePanel(QWidget *parent = nullptr);

    void clearChatSelection();

signals:
    void sideMenuRequested();

    void selectionWasChanged(const ChatModelItemPtr &selectedChat);

    void newChatItemAdded(const ChatItemPtr &chatItem);

private:
    void setupUi();

private:
    ImageButton    *sideMenuButton_ = nullptr;
    SearchLineEdit *searchLineEdit_ = nullptr;
    ChatListView   *chatListView_   = nullptr;
};

#endif // SIDEPANEL_H
