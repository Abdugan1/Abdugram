#include "messageside.h"
#include "messagetextedit.h"
#include "imagebutton.h"

#include <QBoxLayout>
#include <QDebug>

MessageSide::MessageSide(QWidget *parent)
    : QFrame{parent}
{
    setupUi();

    connect(sendButton_, &ImageButton::clicked, messageTextEdit_, &MessageTextEdit::sendMessage);
    connect(messageTextEdit_, &MessageTextEdit::sendMessageRequest, this, &MessageSide::sendMessageRequest);
}

void MessageSide::setupUi()
{
    messageTextEdit_ = new MessageTextEdit;

    sendButton_ = new ImageButton{QPixmap{":/images/back_button.png"}};
    sendButton_->setShortcut(QKeySequence{Qt::Key_Return});

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->setContentsMargins(0, 0, 0, 0);
    hLayout->setSpacing(0);
    hLayout->addWidget(messageTextEdit_);
    hLayout->addWidget(sendButton_, 0, Qt::AlignRight | Qt::AlignBottom);

    setLayout(hLayout);
}
