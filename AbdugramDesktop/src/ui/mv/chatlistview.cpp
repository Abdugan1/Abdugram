#include "ui/mv/chatlistview.h"
#include "ui/mv/chatlistmodel.h"
#include "ui/mv/chatlistdelegate.h"
#include "ui/mv/chatitem.h"
#include "ui/mv/founduseritem.h"

#include "ui/components/scrollbar.h"

#include "net/networkhandler.h"

#include <sql_common/data_structures/user.h>

#include <sql_client/databaseclient.h>
#include <sql_client/sqlquery.h>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QPainter>
#include <QMouseEvent>

ChatListView::ChatListView(QWidget *parent)
    : QListView{parent}
    , mainModel_{new ChatListModel{this}}
    , tempModel_{new ChatListModel{this}}
    , delegate_{new ChatListDelegate{this}}
{
    connect(networkHandler(), &NetworkHandler::syncFinished, this, &ChatListView::initMainModel);

    connect(networkHandler(), &NetworkHandler::searchResult, this, &ChatListView::addFoundUsers);

    connect(networkHandler(), &NetworkHandler::loggedOut, this, &ChatListView::onLoggedOut);

    connect(database(), &DatabaseClient::foundChats, this, &ChatListView::onChatsFound);

    setModel(mainModel_);
    setItemDelegate(delegate_);

    setMouseTracking(true);

    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);

    setVerticalScrollBar(new ScrollBar{Qt::Vertical, this});
    setVerticalScrollMode(QListView::ScrollPerPixel);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);    

    setContentsMargins(0, 0, 0, 0);
    setFrameShape(NoFrame);
}

void ChatListView::setMainModel()
{
    setModel(mainModel_);
}

void ChatListView::setMainModelSelected(int chatId)
{
    setMainModel();
    setCurrentIndex(mainModel_->index(mainModel_->rowByChatId(chatId)));
}

void ChatListView::addFoundUsers(const QList<User> &foundUsers)
{
    QList<FoundUserItemPtr> chatItems;
    for (const auto &foundUser : foundUsers) {
        std::shared_ptr<FoundUserItem> chatItem{new FoundUserItem};
        chatItem->setUserId(foundUser.id());
        chatItem->setUserName(foundUser.username());
        chatItems.append(chatItem);
    }
    tempModel_->addFoundUserItems(chatItems);

    this->setModel(tempModel_);
}

void ChatListView::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    if (selected.empty())
        return;

    QModelIndex selectedIndex = selected.indexes().first();
    if (!selectedIndex.isValid())
        return;

    if (!selectionByUser_)
        return;

    auto model = static_cast<const ChatListModel*>(this->model());
    if (!model)
        return;

    if (selectedIndex.data(ChatModelItem::Roles::Type).toInt() == ChatModelItem::Type::FoundUserItem) {
        emit foundUserSelected(model->chatModelItem(selectedIndex.row()));
        return;
    }

    if ((model == tempModel_)
        && (selectedIndex.data(ChatModelItem::Roles::Type).toInt() == ChatModelItem::Type::ChatItem)) {
        setMainModelSelected(selectedIndex.data(ChatItem::Roles::ChatId).toInt());
    } else {
        setMainModel();
    }

    emit chatSelected(model->chatModelItem(selectedIndex.row()));
}

void ChatListView::mouseMoveEvent(QMouseEvent *event)
{
    const auto index = indexAt(event->pos());

    if (!index.isValid()) {
        setCursor(Qt::ArrowCursor);
    } else {
        const int type = index.data(ChatModelItem::Roles::Type).toInt();
        switch (type) {
        case ChatModelItem::Type::ChatItem:
        case ChatModelItem::Type::FoundUserItem:
            setCursor(Qt::PointingHandCursor);
            break;
        default:
            setCursor(Qt::ArrowCursor);
            break;
        }
    }

    QListView::mouseMoveEvent(event);
}

void ChatListView::enterEvent(QEvent *event)
{
    cursorBeforeEnter_ = cursor();
    QListView::enterEvent(event);
}

void ChatListView::leaveEvent(QEvent *event)
{
    setCursor(cursorBeforeEnter_);
    QListView::leaveEvent(event);
}

void ChatListView::initMainModel()
{
    clearSelection();

    const auto chatViews = database()->getChatsView();
    QList<ChatItemPtr> chatItems;
    for (const auto &chatView : chatViews)
        chatItems.append(ChatItem::fromChatViewItem(chatView));

    mainModel_->setChatItems(chatItems);

    connect(database(), &DatabaseClient::messageAdded, this, &ChatListView::updateMainModel);
    connect(database(), &DatabaseClient::chatAdded, this, &ChatListView::addNewChatToMainModel);
}

void ChatListView::updateMainModel()
{
    const int prevSelectedChatId = currentIndex().data(ChatItem::Roles::ChatId).toInt();
    int indexWithPrevSelectedChatId = -1;

    const auto chatViews = database()->getChatsView();
    QList<ChatItemPtr> chatItems;
    int i = 0;
    for (const auto &chatView : chatViews) {
        chatItems.append(ChatItem::fromChatViewItem(chatView));
        if (chatView.chatId() == prevSelectedChatId) {
            indexWithPrevSelectedChatId = i;
        }
        ++i;
    }

    mainModel_->setChatItems(chatItems);

    selectionByUser_ = false;
    setCurrentIndex(mainModel_->index(indexWithPrevSelectedChatId));
    selectionByUser_ = true;
}

void ChatListView::onLoggedOut()
{
    disconnect(database(), &DatabaseClient::messageAdded, this, &ChatListView::updateMainModel);
    disconnect(database(), &DatabaseClient::chatAdded, this, &ChatListView::addNewChatToMainModel);
    mainModel_->setChatItems({});
}

void ChatListView::addNewChatToMainModel(const Chat &chat)
{
    ChatItemPtr chatItem{new ChatItem};
    chatItem->setChatId(chat.id());
    chatItem->setChatName(chat.name());
    chatItem->setChatType(chat.type());

    mainModel_->addChatItem(chatItem);

    emit newChatItemAdded(chatItem);
}

void ChatListView::onChatsFound(const QList<ChatViewItem> &chatViews)
{
    QList<ChatItemPtr> chatItems;
    for (const auto &chatView : chatViews)
        chatItems.append(ChatItem::fromChatViewItem(chatView));

    tempModel_->setChatItems(chatItems);

    this->setModel(tempModel_);

    emit localSearchFinished();
}
