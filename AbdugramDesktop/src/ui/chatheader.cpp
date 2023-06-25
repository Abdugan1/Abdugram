#include "ui/chatheader.h"
#include "ui/mainlabel.h"
#include "ui/secondarylabel.h"

#include "net/networkhandler.h"

#include <QVBoxLayout>

ChatHeader::ChatHeader(QWidget *parent)
    : QFrame{parent}
{
    setupUi();

    connect(networkHandler(), &NetworkHandler::connectionError, this, &ChatHeader::setLastOnlineLabelAsConnecting);
//    connect(networkHandler(), &NetworkHandler::connectedSucessfully, this, )
}

void ChatHeader::setChatName(const QString &text)
{
    chatName_->setText(text);
}

void ChatHeader::setLastOnlineLabelAsConnecting()
{
    lastOnlineLabel_->setText("Connecting...");
}

void ChatHeader::requestLastOnlineTimeOfCurrentUser()
{
    const QString username = chatName_->text();
}

void ChatHeader::setupUi()
{
    chatName_        = new MainLabel{"Nurzhan"};
    lastOnlineLabel_ = new SecondaryLabel{"last seen 3 hours ago"};
    lastOnlineLabel_->setObjectName("small-font");

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);
    vLayout->addWidget(chatName_);
    vLayout->addWidget(lastOnlineLabel_);

    setLayout(vLayout);
}
