#include "ui/mv/chatlistmodel.h"
#include "ui/mv/lineseparatoritem.h"

#include <net/networkhandler.h>

#include <sql_common/data_structures/user.h>
#include <sql_common/data_structures/chatuser.h>

#include <sql_client/userstable.h>
#include <sql_client/chatstable.h>
#include <sql_client/chatuserstable.h>

#include <QModelIndex>

ChatListModel::ChatListModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

int ChatListModel::rowCount(const QModelIndex &) const
{
    return chatItems_.count();
}

QVariant ChatListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant{};

    return chatItems_[index.row()]->data(role);
}

Qt::ItemFlags ChatListModel::flags(const QModelIndex &index) const
{
    const int type = index.data(ChatModelItem::Roles::Type).toInt();

    switch (type) {
    case ChatModelItem::Type::ChatItem:
    case ChatModelItem::Type::FoundUserItem:
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }

    return Qt::NoItemFlags;
}

void ChatListModel::addChatItem(const ChatModelItemPtr &item)
{
    const int row = chatItems_.count();
    beginInsertRows(QModelIndex(), row, row);
    chatItems_.append(item);
    endInsertRows();
}

ChatModelItemPtr ChatListModel::chatItem(int row) const
{
    return chatItems_.at(row);
}

void ChatListModel::setChatItems(const QList<ChatModelItemPtr> &chatItems)
{
    int oldSize = chatItems_.size();
    chatItems_.clear();
    chatItems_.reserve(chatItems.size() * 2 - 1);
    for (const auto &item : chatItems) {
        chatItems_.append(item);
        chatItems_.append(ChatModelItemPtr{new LineSeparatorItem});
    }
    emit dataChanged(index(0, 0), index(oldSize, 0));
}
