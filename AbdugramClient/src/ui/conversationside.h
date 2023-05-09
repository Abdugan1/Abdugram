#ifndef CONVERSATIONSIDE_H
#define CONVERSATIONSIDE_H

#include <QWidget>

class ChatHeader;
class MessageListView;
class MessageSide;

class ConversationSide : public QWidget
{
    Q_OBJECT
public:
    explicit ConversationSide(QWidget *parent = nullptr);

private:
    void setupUi();

private:
    ChatHeader      *chatHeader_  = nullptr;
    MessageListView *messageView_ = nullptr;
    MessageSide     *messageSide_ = nullptr;

};

#endif // CONVERSATIONSIDE_H
