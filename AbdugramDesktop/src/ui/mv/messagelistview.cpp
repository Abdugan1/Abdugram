#include "ui/mv/messagelistview.h"
#include "ui/mv/messagelistmodel.h"
#include "ui/mv/messagelistdelegate.h"

#include "ui/components/scrollbar.h"

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
    connect(database(), &DatabaseClient::messageAdded, this, &MessageListView::scrollToBottomIfSenderIsMe);

    setModel(model_);
    setItemDelegate(delegate_);

    setVerticalScrollMode(QListView::ScrollPerPixel);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBar(new ScrollBar{Qt::Vertical, this});

    setContentsMargins(0, 0, 0, 0);
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

void MessageListView::scrollToBottomIfSenderIsMe(const Message &message)
{
    if (message.senderId() == networkHandler()->userId()) {
        scrollToBottom();
    }
}
