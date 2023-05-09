#include "conversationside.h"
#include "chatheader.h"
#include "mv/messagelistview.h"
#include "messageside.h"

#include <QVBoxLayout>

ConversationSide::ConversationSide(QWidget *parent)
    : QWidget{parent}
{
    setupUi();
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
