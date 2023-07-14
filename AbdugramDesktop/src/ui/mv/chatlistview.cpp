#include "ui/mv/chatlistview.h"
#include "ui/mv/chatlistmodel.h"
#include "ui/mv/chatlistdelegate.h"
#include "ui/mv/founduserchatitem.h"

#include "net/networkhandler.h"

#include <sql_common/data_structures/user.h>

#include <sql_client/databaseclient.h>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QPainter>

ChatItemPtr getChatItemFromChatsViewRecord(const QSqlRecord &record)
{
    ChatItemPtr chatItem{new ChatItem};
    chatItem->setChatId(record.value("chat_id").toInt());
    chatItem->setChatName(record.value("chat_name").toString());
    chatItem->setChatType(Chat::stringToType(record.value("chat_type").toString()));
    chatItem->setLastMessage(record.value("last_message").toString());
    chatItem->setMessageDate(record.value("last_message_time").toDateTime());

    return chatItem;
}

ChatListView::ChatListView(QWidget *parent)
    : QListView{parent}
    , mainModel_{new ChatListModel{this}}
    , tempModel_{new ChatListModel{this}}
    , delegate_{new ChatListDelegate{this}}
{
    connect(networkHandler(), &NetworkHandler::syncFinished, this, &ChatListView::initMainModel);

    connect(networkHandler(), &NetworkHandler::searchResult, this, &ChatListView::setTemporaryModel);

    connect(database(), &DatabaseClient::messageAdded, this, &ChatListView::updateMainModel);

    setModel(mainModel_);
    setItemDelegate(delegate_);

    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);

    setVerticalScrollMode(QListView::ScrollPerPixel);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setContentsMargins(0, 0, 0, 0);
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

    if (selectionByUser_) {
        if (auto model = static_cast<const ChatListModel*>(this->model()))
            emit selectionWasChangedByUser(model->chatItem(selectedIndex.row()));
    }
}

void ChatListView::initMainModel()
{
    clearSelection();

    QSqlQuery query = database()->getChatsView();
    QVector<ChatItemPtr> chatItems;
    chatItems.reserve(query.size());
    while (query.next()) {
        chatItems.append(getChatItemFromChatsViewRecord(query.record()));
    }

    mainModel_->setChatItems(chatItems);
}

void ChatListView::updateMainModel()
{
    const int prevSelectedChatId = currentIndex().data(ChatListModel::Roles::Id).toInt();
    int indexWithPrevSelectedChatId = -1;

    QSqlQuery query = database()->getChatsView();
    QVector<ChatItemPtr> chatItems;
    chatItems.reserve(query.size());
    int i = 0;
    while (query.next()) {
        chatItems.append(getChatItemFromChatsViewRecord(query.record()));
        if (chatItems.last()->chatId() == prevSelectedChatId) {
            indexWithPrevSelectedChatId = i;
        }
        ++i;
    }

    mainModel_->setChatItems(chatItems);

    selectionByUser_ = false;
    setCurrentIndex(mainModel_->index(indexWithPrevSelectedChatId));
    selectionByUser_ = true;
}
