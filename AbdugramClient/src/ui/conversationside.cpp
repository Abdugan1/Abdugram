#include "conversationside.h"
#include "chatheader.h"
#include "mv/messagelistview.h"
#include "messageside.h"

#include "net/networkhandler.h"

#include <net_common/messages/createchatmessage.h>

#include <sql_common/data_structures/chat.h>
#include <sql_common/data_structures/chatuser.h>

#include <QVBoxLayout>
#include <QDebug>

ConversationSide::ConversationSide(QWidget *parent)
    : QWidget{parent}
{
    setupUi();

    connect(messageSide_, &MessageSide::sendMessageRequest, this, [this]() {
        if (currentChat_.id() == -1) {
            requestCreatePrivateChat();
        }
    });
}

void ConversationSide::setCurrentChat(const ChatItem &chat)
{
    currentChat_ = chat;
    if (chat.id() == -1) {
        chatHeader_->setChatName(chat.chatName());
    }
}

void ConversationSide::requestCreatePrivateChat()
{
    if (currentChat_.userId() == -1) {
        qCritical() << "Can't create private chat! current chat user id is undefined";
        return;
    }

    Chat chat;
    chat.setType(Chat::Type::Private);

    ChatUser chatUser1;
    chatUser1.setUserId(networkHandler()->userId());
    chatUser1.setRole(ChatUser::Role::Owner);

    ChatUser chatUser2;
    chatUser2.setUserId(currentChat_.userId());
    chatUser2.setRole(ChatUser::Role::Owner);

    AnyMessagePtr<CreateChatMessage> createPrivateChat{new CreateChatMessage};
    createPrivateChat->setChat(chat);
    createPrivateChat->setChatUsers({chatUser1, chatUser2});

    networkHandler()->sendToServer(static_cast<AbduMessagePtr>(createPrivateChat));
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
