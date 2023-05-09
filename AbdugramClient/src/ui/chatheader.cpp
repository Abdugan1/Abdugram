#include "chatheader.h"
#include "mainlabel.h"
#include "secondarylabel.h"

#include <QVBoxLayout>

ChatHeader::ChatHeader(QWidget *parent)
    : QFrame{parent}
{
    setupUi();
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
