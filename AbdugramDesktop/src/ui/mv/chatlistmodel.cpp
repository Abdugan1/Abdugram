#include "ui/mv/chatlistmodel.h"
#include "ui/mv/chatitem.h"
#include "ui/mv/founduseritem.h"
#include "ui/mv/sectionseparator.h"

#include <net/networkhandler.h>

#include <sql_common/data_structures/user.h>
#include <sql_common/data_structures/chatuser.h>

#include <sql_client/userstable.h>
#include <sql_client/chatstable.h>
#include <sql_client/chatuserstable.h>

#include <QModelIndex>

#include <algorithm>

ChatListModel::ChatListModel(QObject *parent)
    : QAbstractListModel{parent}
{
}

int ChatListModel::rowCount(const QModelIndex &) const
{
    return chatModelItems_.count();
}

QVariant ChatListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant{};

    return chatModelItems_[index.row()]->data(role);
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

void ChatListModel::addChatItem(const ChatItemPtr &item)
{
    const int row = chatModelItems_.count();
    beginInsertRows(QModelIndex(), row, row);
    chatModelItems_.append(item);
    endInsertRows();
}

ChatModelItemPtr ChatListModel::chatModelItem(int row) const
{
    return chatModelItems_.at(row);
}

int ChatListModel::rowByChatId(int id) const
{
    int row = 0;
    for (const auto &item : chatModelItems_) {
        if ((item->data(ChatModelItem::Roles::Type).toInt() == ChatModelItem::Type::ChatItem)
            && item->data(ChatItem::Roles::ChatId).toInt() == id) {
            return row;
        }
        row++;
    }
    return -1;
}

void ChatListModel::setChatItems(const QList<ChatItemPtr> &chatItems)
{
    int oldSize = chatModelItems_.size();
    chatModelItems_.clear();
    chatModelItems_.reserve(chatItems.size());
    for (const auto &item : chatItems) {
        chatModelItems_.append(item);
    }
    emit dataChanged(index(0, 0), index(oldSize, 0));
}

void ChatListModel::addFoundUserItems(const QList<FoundUserItemPtr> &foundUsers)
{
    const int row = chatModelItems_.count();
    beginInsertRows(QModelIndex{}, row, row + foundUsers.count() - 1 + 1  /* string delim */);

    chatModelItems_.reserve(chatModelItems_.count() + foundUsers.count() + 1);

    chatModelItems_.append(ChatModelItemPtr{new SectionSeparator{tr("Global search result")}});
    for (const auto &foundUser : foundUsers) {
        chatModelItems_.append(foundUser);
    }

    endInsertRows();
}
