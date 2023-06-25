#include "ui/mv/messagelistmodel.h"
#include "ui/mv/messageitem.h"

#include <sql_client/databaseclient.h>

#include <sql_common/data_structures/message.h>

#include <QDebug>

MessageListModel::MessageListModel(QObject *parent)
    : QAbstractListModel{parent}
{
    connect(database(), &DatabaseClient::messageAdded, this, &MessageListModel::onMessageAdded);
}

int MessageListModel::rowCount(const QModelIndex &) const
{
    return messageItems_.count();
}

QVariant MessageListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant{};

    const auto &messageItem = messageItems_.at(index.row());
    switch (role) {
    case Text:     return messageItem.text();     break;
    case DateTime: return messageItem.dateTime(); break;
    case SenderId: return messageItem.senderId(); break;
    }

    return QVariant{};
}

bool MessageListModel::isEmpty() const
{
    return messageItems_.isEmpty();
}

int MessageListModel::chatId() const
{
    return chatId_;
}

void MessageListModel::setChatId(int newChatId)
{
    chatId_ = newChatId;

    const int prevSize = messageItems_.size();
    messageItems_.clear();

    QList<Message> messages = database()->getMessages(newChatId);
    for (const auto &message : messages) {
        messageItems_.append(MessageItem::fromMessage(message));
    }

    emit dataChanged(index(0, 0), index(prevSize, 0));
}

void MessageListModel::onMessageAdded(const Message &message)
{
    if (chatId_ != message.chatId())
        return;

    const int row = messageItems_.count();
    beginInsertRows(QModelIndex(), row, row);
    messageItems_.append(MessageItem::fromMessage(message));
    endInsertRows();
}
