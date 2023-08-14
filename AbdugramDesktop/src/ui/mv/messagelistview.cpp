#include "ui/mv/messagelistview.h"
#include "ui/mv/messagelistmodel.h"
#include "ui/mv/messagelistdelegate.h"

#include "ui/components/scrollbar.h"
#include "ui/components/notificationmanager.h"

#include "net/networkhandler.h"

#include <sql_common/data_structures/message.h>

#include <sql_client/databaseclient.h>

#include <QPainter>
#include <QDebug>

MessageListView::MessageListView(QWidget *parent)
    : QListView{parent}
    , model_{new MessageListModel{this}}
    , delegate_{new MessageListDelegate{this}}
{
    connect(database(), &DatabaseClient::messageAdded, this, &MessageListView::scrollToBottomIfSenderIsMeOrIfShouldScroll);

    connect(networkHandler(), &NetworkHandler::syncFinished, this, [this]() {
        connect(database(), &DatabaseClient::messageAdded, this, &MessageListView::showNotificationIfMessageIdIsNotCurrent);
    });

    connect(networkHandler(), &NetworkHandler::loggedOut, this, [this]() {
        disconnect(database(), &DatabaseClient::messageAdded, this, &MessageListView::showNotificationIfMessageIdIsNotCurrent);
    });

    setModel(model_);
    setItemDelegate(delegate_);

    setVerticalScrollMode(QListView::ScrollPerPixel);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBar(new ScrollBar{Qt::Vertical, this});
    setFocusPolicy(Qt::NoFocus);

    setContentsMargins(0, 0, 0, 0);

    connect(verticalScrollBar(), &ScrollBar::valueChanged, this, [this](int value) {
        shouldScroll_ = (value == verticalScrollBar()->maximum());
    });
}

void MessageListView::setChatId(int chatId)
{
    model_->setChatId(chatId);
    scrollToBottom();
}

void MessageListView::setChatIdWithoutSelect(int chatId)
{
    model_->setChatIdWithoutSelect(chatId);
    scrollToBottom();
}

void MessageListView::scrollToBottomIfSenderIsMeOrIfShouldScroll(const Message &message)
{
    if (shouldScroll_ || message.senderId() == networkHandler()->userId()) {
        scrollToBottom();
    }
}

void MessageListView::showNotificationIfMessageIdIsNotCurrent(const Message &message)
{
    if (message.senderId() == networkHandler()->userId() || message.chatId() == model_->chatId())
        return;

    emit notificationRequested(message);

    notificationManager()->addNotification(message);
}
