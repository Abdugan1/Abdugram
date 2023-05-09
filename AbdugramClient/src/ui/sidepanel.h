#ifndef SIDEPANEL_H
#define SIDEPANEL_H

#include <QWidget>

#include <net_common/messages/abdumessage.h>

class ImageButton;
class SearchLineEdit;
class ChatListView;

class ChatItem;

class SidePanel : public QWidget
{
    Q_OBJECT
public:
    explicit SidePanel(QWidget *parent = nullptr);

signals:
    void selectionWasChanged(const ChatItem &selectedChat);

private:
    void setupUi();

private:
    ImageButton    *openDrawer_     = nullptr;
    SearchLineEdit *searchLineEdit_ = nullptr;
    ChatListView   *chatListView_   = nullptr;
};

#endif // SIDEPANEL_H
