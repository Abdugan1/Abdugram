#ifndef CONVERSATIONSIDE_H
#define CONVERSATIONSIDE_H

#include <QWidget>

#include "mv/chatitem.h"

class ChatHeader;
class MessageListView;
class MessageSide;

class ConversationSide : public QWidget
{
    Q_OBJECT
public:
    explicit ConversationSide(QWidget *parent = nullptr);

    ChatItem currentChat() const;

public slots:
    void setCurrentChat(const ChatItemPtr &chat);

    void checkCurrentChat(const ChatItemPtr &chat);

private slots:
    void requestCreatePrivateChat();

private:
    void setupUi();

private:
    ChatHeader      *chatHeader_  = nullptr;
    MessageListView *messageView_ = nullptr;
    MessageSide     *messageSide_ = nullptr;

    ChatItemPtr currentChat_;
};

#endif // CONVERSATIONSIDE_H
