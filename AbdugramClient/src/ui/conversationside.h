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

public slots:
    void setCurrentChat(const ChatItem &chat);

private slots:
    void requestCreatePrivateChat();

private:
    void setupUi();

private:
    ChatHeader      *chatHeader_  = nullptr;
    MessageListView *messageView_ = nullptr;
    MessageSide     *messageSide_ = nullptr;

    ChatItem currentChat_;
};

#endif // CONVERSATIONSIDE_H
