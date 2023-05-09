#include "messageside.h"
#include "messagetextedit.h"
#include "imagebutton.h"

#include <QBoxLayout>

MessageSide::MessageSide(QWidget *parent)
    : QFrame{parent}
{
    setupUi();
}

void MessageSide::setupUi()
{
    messageTextEdit_    = new MessageTextEdit;
    sendButton_         = new ImageButton{QPixmap{":/images/back_button.png"}};

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->setSpacing(0);
    hLayout->addWidget(messageTextEdit_);
    hLayout->addWidget(sendButton_, 0, Qt::AlignRight | Qt::AlignBottom);

    setLayout(hLayout);
}
