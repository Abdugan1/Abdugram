#include "ui/components/chatheader.h"
#include "ui/components/conversationside.h"
#include "ui/components/messagetextedit.h"
#include "ui/components/colorrepository.h"

#include "ui/mv/messagelistview.h"
#include "ui/mv/founduseritem.h"

#include "ui/mv/chatitem.h"

#include "net/networkhandler.h"

#include <net_common/messages/createchatrequest.h>
#include <net_common/messages/sendmessagerequest.h>

#include <sql_common/data_structures/chat.h>
#include <sql_common/data_structures/chatuser.h>

#include <sql_client/chatstable.h>

#include <QVBoxLayout>
#include <QPainter>
#include <QDebug>

ConversationSide::ConversationSide(QWidget *parent)
    : QWidget{parent}
{
    setupUi();

    connect(messageEdit_, &MessageTextEdit::sendMessageRequest,
            this,         &ConversationSide::onSendMessageRequested);

    connect(networkHandler(), &NetworkHandler::loggedOut, this, &ConversationSide::unsetCurrentChatItem);
}

void ConversationSide::paintEvent(QPaintEvent *event)
{
    if (!currentChatItem_) {
        drawOnNoChatSelected();
    } else {
        QWidget::paintEvent(event);
    }
}

void ConversationSide::setCurrentChatItem(const ChatModelItemPtr &chat)
{
    const auto prevChat = currentChatItem_;
    currentChatItem_ = chat;

    if (!currentChatItem_) {
        hideAll();
        return;
    } else {
        if (!messageView_->isVisible())
            showAll();
        messageEdit_->setFocus(Qt::MouseFocusReason);
    }

    const int type = chat->data(ChatModelItem::Roles::Type).toInt();

    const auto FoundUserItem = ChatModelItem::Type::FoundUserItem;
    const auto ChatItem      = ChatModelItem::Type::ChatItem;

    if (prevChat) {
        const int prevType = prevChat->data(ChatModelItem::Roles::Type).toInt();
        if (prevType == FoundUserItem && type == ChatItem) {
            if (prevChat->data(FoundUserItem::Username) == currentChatItem_->data(ChatItem::ChatName)) {
                messageView_->setChatIdWithoutSelect(currentChatItem_->data(ChatItem::ChatId).toInt());
                return;
            }
        }
        update();
    }

    if (type == ChatItem) {
        chatHeader_->setChatName(chat->data(ChatItem::Roles::ChatName).toString());
        messageView_->setChatId(chat->data(ChatItem::Roles::ChatId).toInt());
    } else if (type == FoundUserItem) {
        chatHeader_->setChatName(chat->data(FoundUserItem::Roles::Username).toString());
        messageView_->setChatId(-1);
    }
    update();
}

void ConversationSide::unsetCurrentChatItem()
{
    setCurrentChatItem(nullptr);
}

void ConversationSide::updateCurrentChatIfAddedChatIsEqualToAdded(const ChatItemPtr &chat)
{
    if (!currentChatItem_)
        return;
    const int type = currentChatItem_->data(ChatModelItem::Roles::Type).toInt();
    if (type == ChatModelItem::Type::FoundUserItem) {
        emit addedChatWasCurrent(chat->data(ChatItem::Roles::ChatId).toInt());
    }
}

void ConversationSide::requestCreatePrivateChat(const QString &messageText)
{
    Chat chat;
    chat.setType(Chat::Type::Private);

    ChatUser chatUser1;
    chatUser1.setUserId(networkHandler()->userId());
    chatUser1.setRole(ChatUser::Role::Owner);

    ChatUser chatUser2;
    chatUser2.setUserId(currentChatItem_->data(FoundUserItem::Roles::UserId).toInt());
    chatUser2.setRole(ChatUser::Role::Owner);

    Message message;
    message.setSenderId(networkHandler()->userId());
    message.setText(messageText);

    networkHandler()->sendCreatePrivateChatRequest(chat, {chatUser1, chatUser2}, message);
}

void ConversationSide::requestSendMessage(const QString &messageText)
{
    Message message;
    message.setChatId(currentChatItem_->data(ChatItem::Roles::ChatId).toInt());
    message.setSenderId(networkHandler()->userId());
    message.setText(messageText);

    networkHandler()->sendSendMessageRequest(message);
}

void ConversationSide::onSendMessageRequested(const QString &messageText)
{
    const int type = currentChatItem_->data(ChatModelItem::Roles::Type).toInt();
    if (type == ChatModelItem::Type::FoundUserItem) {
        requestCreatePrivateChat(messageText);
    } else {
        requestSendMessage(messageText);
    }
}

void ConversationSide::setupUi()
{
    chatHeader_  = new ChatHeader;
    messageView_ = new MessageListView;
    messageEdit_ = new MessageTextEdit;

    hideAll();

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);
    vLayout->addWidget(chatHeader_);
    vLayout->addWidget(messageView_, 1);
    vLayout->addWidget(messageEdit_);

    setLayout(vLayout);

    QPalette p = palette();
    p.setColor(QPalette::Base, Colors.value(colornames::backgroundColor));
    p.setColor(QPalette::Window, Colors.value(colornames::backgroundColor));
    setPalette(p);
}

void ConversationSide::showAll()
{
    chatHeader_->show();
    messageView_->show();
    messageEdit_->show();
}

void ConversationSide::hideAll()
{
    chatHeader_->hide();
    messageView_->hide();
    messageEdit_->hide();
}

void ConversationSide::drawOnNoChatSelected()
{
    QPainter painter{this};
    painter.setRenderHint(QPainter::Antialiasing);

    const QFontMetrics fm = painter.fontMetrics();
    const QString text    = tr("Select a chat to start messaging");
    const QRect textBRect = fm.boundingRect(text);
    const QPoint center = rect().center();

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor{Colors.value("decorationColor")});
    const int hMargin = 15;
    const int vMargin = 3;
    QRect background = QRect{center.x() - textBRect.width() / 2 - hMargin,
                             center.y() - fm.ascent() / 2 - vMargin,
                             textBRect.width() + 2 * hMargin,
                             textBRect.height() + 2 * vMargin};
    painter.drawRoundedRect(background, background.height() / 2, background.height() / 2);

    painter.setPen(QColor{Colors.value("mainLabelColor")});

    const QPoint textDrawPoint{center.x() - fm.horizontalAdvance(text) / 2,
                               center.y() + fm.ascent() / 2};

    painter.drawText(textDrawPoint, text);
}
