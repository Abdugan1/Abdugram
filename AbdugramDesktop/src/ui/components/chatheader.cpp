#include "ui/components/chatheader.h"
#include "ui/components/mainlabel.h"
#include "ui/components/secondarylabel.h"

#include "ui/components/colorrepository.h"

#include "net/networkhandler.h"

#include <QVBoxLayout>

ChatHeader::ChatHeader(QWidget *parent)
    : Widget{parent}
{
    setupUi();

    connect(networkHandler(), &NetworkHandler::connectionError, this, &ChatHeader::setLastOnlineLabelAsConnecting);
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
    chatName_        = new MainLabel;
    lastOnlineLabel_ = new SecondaryLabel{"last seen 3 hours ago"};
    lastOnlineLabel_->setObjectName("small-font");

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->setContentsMargins(10, 10, 10, 10);
    vLayout->setSpacing(0);
    vLayout->addWidget(chatName_);
    vLayout->addWidget(lastOnlineLabel_);

    setLayout(vLayout);
    setBackgroundColor(Colors.value(colornames::backgroundLighterHelper1));
}
