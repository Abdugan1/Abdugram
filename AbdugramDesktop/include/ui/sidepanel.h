#ifndef SIDEPANEL_H
#define SIDEPANEL_H

#include <QFrame>

#include <net_common/messages/abdumessage.h>

#include "mv/chatitem.h"

class QFrame;

class ImageButton;
class SearchLineEdit;
class ChatListView;

class SidePanel : public QFrame
{
    Q_OBJECT
public:
    explicit SidePanel(QWidget *parent = nullptr);

signals:
    void sideMenuRequested();

    void selectionWasChanged(const ChatItemPtr &selectedChat);

    void newChatItemAdded(const ChatItemPtr &chatItem);

private slots:
    void addNewChatToView(const Chat &chat);

private:
    void setupUi();

private:
    ImageButton    *sideMenuButton_ = nullptr;
    SearchLineEdit *searchLineEdit_ = nullptr;
    ChatListView   *chatListView_   = nullptr;
};

#endif // SIDEPANEL_H
