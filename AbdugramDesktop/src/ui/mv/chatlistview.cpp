#include "ui/mv/chatlistview.h"
#include "ui/mv/chatlistmodel.h"
#include "ui/mv/chatlistdelegate.h"
#include "ui/mv/founduserchatitem.h"

#include "net/networkhandler.h"

#include <sql_common/data_structures/user.h>

#include <sql_client/databaseclient.h>

#include <QPainter>

ChatListView::ChatListView(QWidget *parent)
    : QListView{parent}
    , mainModel_{new ChatListModel{this}}
    , tempModel_{new ChatListModel{this}}
    , delegate_{new ChatListDelegate{this}}
{
    connect(networkHandler(), &NetworkHandler::syncFinished, this, &ChatListView::initMainModel);

    connect(this, &ChatListView::chatNameColorChanged, this, [this]() {
        delegate_->setChatNameColor(chatNameColor_);
    });
    connect(this, &ChatListView::lastMessageColorChanged, this, [this]() {
        delegate_->setLastMessageColor(lastMessageColor_);
    });
    connect(this, &ChatListView::messageDateColorChanged, this, [this]() {
        delegate_->setMessageDateColor(messageDateColor_);
    });
    connect(this, &ChatListView::highlightColorChanged, this, [this]() {
        delegate_->setHighlightColor(highlightColor_);
    });

    connect(networkHandler(), &NetworkHandler::searchResult, this, &ChatListView::setTemporaryModel);

    setModel(mainModel_);
    setItemDelegate(delegate_);

    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);

    setVerticalScrollMode(QListView::ScrollPerPixel);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setContentsMargins(0, 0, 0, 0);
}

QColor ChatListView::chatNameColor() const
{
    return chatNameColor_;
}

void ChatListView::setChatNameColor(const QColor &newChatNameColor)
{
    if (chatNameColor_ == newChatNameColor)
        return;
    chatNameColor_ = newChatNameColor;
    emit chatNameColorChanged();
}

QColor ChatListView::lastMessageColor() const
{
    return lastMessageColor_;
}

void ChatListView::setLastMessageColor(const QColor &newLastMessageColor)
{
    if (lastMessageColor_ == newLastMessageColor)
        return;
    lastMessageColor_ = newLastMessageColor;
    emit lastMessageColorChanged();
}

QColor ChatListView::messageDateColor() const
{
    return messageDateColor_;
}

void ChatListView::setMessageDateColor(const QColor &newMessageDateColor)
{
    if (messageDateColor_ == newMessageDateColor)
        return;
    messageDateColor_ = newMessageDateColor;
    emit messageDateColorChanged();
}

QColor ChatListView::highlightColor() const
{
    return highlightColor_;
}

void ChatListView::setHighlightColor(const QColor &newHighlightColor)
{
    if (highlightColor_ == newHighlightColor)
        return;
    highlightColor_ = newHighlightColor;
    emit highlightColorChanged();
}

void ChatListView::addNewChatItemToMainModel(const ChatItemPtr &chatItem)
{
    mainModel_->addChatItem(chatItem);
}

void ChatListView::setMainModel()
{
    setModel(mainModel_);
}

void ChatListView::setTemporaryModel(const QList<User> &foundUserList)
{
    QVector<ChatItemPtr> chatItems;
    chatItems.reserve(foundUserList.size());
    for (const auto &foundUser : foundUserList) {
        std::shared_ptr<FoundUserChatItem> chatItem{new FoundUserChatItem};
        chatItem->setUserId(foundUser.id());
        chatItem->setChatName(foundUser.username());
        chatItems.append(chatItem);
    }
    tempModel_->setChatItems(chatItems);
    this->setModel(tempModel_);
}

void ChatListView::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    if (selected.empty())
        return;

    QModelIndex selectedIndex = selected.indexes().first();
    if (!selectedIndex.isValid())
        return;

    if (auto model = static_cast<const ChatListModel*>(this->model()))
        emit selectionWasChanged(model->chatItem(selectedIndex.row()));
}

void ChatListView::initMainModel()
{
    clearSelection();
    const QList<Chat> chats = database()->getAllChats();

    QVector<ChatItemPtr> chatItems;
    chatItems.reserve(chats.size());
    for (const auto &chat : chats) {
        ChatItemPtr chatItem{new ChatItem};
        chatItem->setChatId(chat.id());
        chatItem->setChatName(chat.name());
        chatItem->setChatType(chat.type());
        chatItems.append(chatItem);
    }

    mainModel_->setChatItems(chatItems);
}
