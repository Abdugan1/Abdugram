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
    return *currentChatItem_;
}

void ConversationSide::setCurrentChatItem(const ChatItemPtr &chat)
{
    currentChatItem_ = chat;
    chatHeader_->setChatName(chat->chatName());
    messageView_->setChatId(chat->chatId());
}

void ConversationSide::checkCurrentChatItem(const ChatItemPtr &chat)
{
    if (currentChatItem_ && currentChatItem_->chatName() == chat->chatName()) {
        setCurrentChatItem(chat);
    }
}

void ConversationSide::requestCreatePrivateChat()
{
    auto currentChatItem = dynamic_cast<FoundUserChatItem *>(currentChatItem_.get());
    if (currentChatItem && currentChatItem->userId() == -1) {
        qCritical() << "Can't create private chat! current chat user id is undefined";
        return;
    }

    Chat chat;
    chat.setType(Chat::Type::Private);

    ChatUser chatUser1;
    chatUser1.setUserId(networkHandler()->userId());
    chatUser1.setRole(ChatUser::Role::Owner);

    ChatUser chatUser2;
    chatUser2.setUserId(currentChatItem->userId());
    chatUser2.setRole(ChatUser::Role::Owner);


    networkHandler()->sendCreateChatRequest(chat, {chatUser1, chatUser2});
}

void ConversationSide::onSendMessageRequested(const QString &messageText)
{
    if (currentChatItem_->chatId() == -1) {
        requestCreatePrivateChat();
    } else {
        Message message;
        message.setChatId(currentChatItem_->chatId());
        message.setSenderId(networkHandler()->userId());
        message.setText(messageText);

        networkHandler()->sendSendMessageRequest(message);
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
