#ifndef SIDEPANEL_H
#define SIDEPANEL_H

#include <QWidget>

#include <net_common/messages/abdumessage.h>

#include "mv/chatitem.h"

class ImageButton;
class SearchLineEdit;
class ChatListView;

class SidePanel : public QWidget
{
    Q_OBJECT
public:
    explicit SidePanel(QWidget *parent = nullptr);

signals:
    void selectionWasChanged(const ChatItemPtr &selectedChat);

    void newChatItemAdded(const ChatItemPtr &chatItem);

private slots:
    void addNewChatToView(const Chat &chat);

private:
    void setupUi();

private:
    ImageButton    *openDrawer_     = nullptr;
    SearchLineEdit *searchLineEdit_ = nullptr;
    ChatListView   *chatListView_   = nullptr;
};

#endif // SIDEPANEL_H
