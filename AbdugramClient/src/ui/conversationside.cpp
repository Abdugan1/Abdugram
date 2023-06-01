#include "conversationside.h"
#include "chatheader.h"
#include "mv/messagelistview.h"
#include "messageside.h"

#include "net/networkhandler.h"

#include <net_common/messages/createprivatechatmessage.h>

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

    AnyMessagePtr<CreatePrivateChatMessage> createPrivateChat{new CreatePrivateChatMessage};

    createPrivateChat->setUser1Id(networkHandler()->userId());
    createPrivateChat->setUser2Id(currentChat_.userId());

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
