#include "chatlistmodel.h"

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
//    connect(networkHandler()->newChatAdded(), this, )
}

int ChatListModel::rowCount(const QModelIndex &) const
{
    return chatItems_.count();
}

QVariant ChatListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant{};
    const ChatItemPtr &chatItem = chatItems_.at(index.row());
    switch (role) {
    case Roles::Avatar:      return chatItem->avatar();      break;
    case Roles::ChatName:    return chatItem->chatName();    break;
    case Roles::LastMessage: return chatItem->lastMessage(); break;
    case Roles::MessageDate: return chatItem->messageDate(); break;
    }

    return QVariant{};
}

void ChatListModel::addChatItem(const ChatItemPtr &item)
{
    const int row = chatItems_.count();
    beginInsertRows(QModelIndex(), row, row);
    chatItems_.append(item);
    endInsertRows();
}

ChatItemPtr ChatListModel::chatItem(int row) const
{
    return chatItems_.at(row);
}

void ChatListModel::setChatItems(const ChatItems &chatItems)
{
    int oldSize = chatItems_.size();
    chatItems_ = chatItems;
    emit dataChanged(index(0, 0), index(oldSize, 0));
}
