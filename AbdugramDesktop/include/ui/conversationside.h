#ifndef CONVERSATIONSIDE_H
#define CONVERSATIONSIDE_H

#include <QWidget>

#include "mv/chatitem.h"

class ChatHeader;
class MessageListView;
class MessageTextEdit;

class ConversationSide : public QWidget
{
    Q_OBJECT
public:
    explicit ConversationSide(QWidget *parent = nullptr);

    ChatItem currentChat() const;

protected:
    void paintEvent(QPaintEvent *event) override;

public slots:
    void setCurrentChatItem(const ChatItemPtr &chat);
    void unsetCurrentChatItem();

    void updateCurrentChatIfAddedChatIsEqualToAdded(const ChatItemPtr &chat);

private slots:
    void requestCreatePrivateChat();

    void onSendMessageRequested(const QString &messageText);

private:
    void setupUi();

    void showAll();
    void hideAll();

    void drawOnNoChatSelected();

private:
    ChatHeader      *chatHeader_  = nullptr;
    MessageListView *messageView_ = nullptr;
    MessageTextEdit *messageEdit_ = nullptr;

    ChatItemPtr currentChatItem_;
};

#endif // CONVERSATIONSIDE_H
