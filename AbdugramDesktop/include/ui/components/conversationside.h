#ifndef CONVERSATIONSIDE_H
#define CONVERSATIONSIDE_H

#include <QWidget>
#include <QModelIndex>

#include <net_common/messages/messagesforwarddeclaration.h>

class ChatHeader;
class MessageListView;
class MessageTextEdit;

class ChatModelItem;
using ChatModelItemPtr = std::shared_ptr<ChatModelItem>;

class ChatItem;
using ChatItemPtr = std::shared_ptr<ChatItem>;

class ConversationSide : public QWidget
{
    Q_OBJECT
public:
    explicit ConversationSide(QWidget *parent = nullptr);

signals:
    void addedChatWasCurrent(int chatId);

protected:
    void paintEvent(QPaintEvent *event) override;

public slots:
    void setCurrentChatItem(const ChatModelItemPtr &chat);
    void unsetCurrentChatItem();

    void updateCurrentChatIfAddedChatIsEqualToAdded(const ChatItemPtr &chat);

private slots:
    void requestCreatePrivateChat(const QString &messageText);
    void requestSendMessage(const QString &messageText);

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

    ChatModelItemPtr currentChatItem_;
};

#endif // CONVERSATIONSIDE_H
