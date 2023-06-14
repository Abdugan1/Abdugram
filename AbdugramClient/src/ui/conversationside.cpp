#include "conversationside.h"
#include "chatheader.h"
#include "mv/messagelistview.h"
#include "mv/founduserchatitem.h"
#include "messageside.h"

#include "net/networkhandler.h"

#include <net_common/messages/createchatmessage.h>
#include <net_common/messages/sendmessagemessage.h>

#include <sql_common/data_structures/chat.h>
#include <sql_common/data_structures/chatuser.h>

#include <sql_client/chatstable.h>

#include <QVBoxLayout>
#include <QDebug>

ConversationSide::ConversationSide(QWidget *parent)
    : QWidget{parent}
{
    setupUi();

    connect(messageSide_, &MessageSide::sendMessageRequest, this, &ConversationSide::onSendMessageRequested);
}

ChatItem ConversationSide::currentChat() const
{
    return *currentChat_;
}

void ConversationSide::setCurrentChat(const ChatItemPtr &chat)
{
    currentChat_ = chat;
    chatHeader_->setChatName(chat->chatName());
    messageView_->setChatId(chat->chatId());
}

void ConversationSide::checkCurrentChat(const ChatItemPtr &chat)
{
    if (chat->chatName() == currentChat_->chatName()) {
        setCurrentChat(chat);
    }
}

void ConversationSide::requestCreatePrivateChat()
{
    auto currentChat = dynamic_cast<FoundUserChatItem *>(currentChat_.get());
    if (currentChat && currentChat->userId() == -1) {
        qCritical() << "Can't create private chat! current chat user id is undefined";
        return;
    }

    Chat chat;
    chat.setType(Chat::Type::Private);

    ChatUser chatUser1;
    chatUser1.setUserId(networkHandler()->userId());
    chatUser1.setRole(ChatUser::Role::Owner);

    ChatUser chatUser2;
    chatUser2.setUserId(currentChat->userId());
    chatUser2.setRole(ChatUser::Role::Owner);

    AnyMessagePtr<CreateChatMessage> createPrivateChat{new CreateChatMessage};
    createPrivateChat->setChat(chat);
    createPrivateChat->setChatUsers({chatUser1, chatUser2});

    networkHandler()->sendToServer(static_cast<AbduMessagePtr>(createPrivateChat));
}

void ConversationSide::onSendMessageRequested(const QString &messageText)
{
    if (currentChat_->chatId() == -1) {
        requestCreatePrivateChat();
    } else {
        qDebug() << "sending message";
        Message message;
        message.setChatId(currentChat_->chatId());
        message.setSenderId(networkHandler()->userId());
        message.setText(messageText);

        AnyMessagePtr<SendMessageMessage> sendMessage{new SendMessageMessage};
        sendMessage->setMessage(message);
        qDebug() << "type:" << static_cast<int>(sendMessage->type());

        networkHandler()->sendToServer(static_cast<AbduMessagePtr>(sendMessage));
    }
}

void ConversationSide::setupUi()
{
    chatHeader_  = new ChatHeader;
    messageView_ = new MessageListView;
    messageSide_ = new MessageSide;

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);
    vLayout->addWidget(chatHeader_);
    vLayout->addWidget(messageView_, 1);
    vLayout->addWidget(messageSide_);

    setLayout(vLayout);
}
