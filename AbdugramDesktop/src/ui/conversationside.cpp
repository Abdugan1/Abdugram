#include "ui/conversationside.h"
#include "ui/chatheader.h"
#include "ui/mv/messagelistview.h"
#include "ui/mv/founduserchatitem.h"
#include "ui/messagetextedit.h"
#include "ui/colorrepository.h"

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

ChatItem ConversationSide::currentChat() const
{
    return *currentChatItem_;
}

void ConversationSide::paintEvent(QPaintEvent *event)
{
    if (!currentChatItem_) {
        drawOnNoChatSelected();
    } else {
        QWidget::paintEvent(event);
    }
}

void ConversationSide::setCurrentChatItem(const ChatItemPtr &chat)
{
    currentChatItem_ = chat;

    if (!currentChatItem_) {
        hideAll();
        return;
    } else if (!messageView_->isVisible()) {
        showAll();
    }

    chatHeader_->setChatName(chat->chatName());
    messageView_->setChatId(chat->chatId());

    update();
}

void ConversationSide::unsetCurrentChatItem()
{
    setCurrentChatItem(nullptr);
}

void ConversationSide::updateCurrentChatIfAddedChatIsEqualToAdded(const ChatItemPtr &chat)
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
    messageEdit_ = new MessageTextEdit;

    hideAll();

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);
    vLayout->addWidget(chatHeader_);
    vLayout->addWidget(messageView_, 1);
    vLayout->addWidget(messageEdit_);

    setLayout(vLayout);
    setFocusPolicy(Qt::ClickFocus);
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

    QFont f = painter.font();
    f.setPointSize(11);
    painter.setFont(f);

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
