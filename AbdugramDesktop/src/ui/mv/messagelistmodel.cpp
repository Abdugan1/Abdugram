#include "ui/mv/messagelistmodel.h"
#include "ui/mv/messageitem.h"
#include "ui/mv/dateseparatoritem.h"

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
    return messageModelItems_.count();
}

QVariant MessageListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant{};

    return messageModelItems_[index.row()]->data(role);
}

bool MessageListModel::isEmpty() const
{
    return messageModelItems_.isEmpty();
}

int MessageListModel::chatId() const
{
    return chatId_;
}

void MessageListModel::setChatId(int newChatId)
{
    chatId_ = newChatId;

    const int prevSize = messageModelItems_.size();
    messageModelItems_.clear();
    lastDate_ = QDate{};

    QList<Message> messages = database()->getMessages(newChatId);
    for (const auto &message : messages) {
        addMessage(message);
    }

    emit dataChanged(index(0, 0), index(prevSize, 0));
}

void MessageListModel::setChatIdWithoutSelect(int newChatId)
{
    chatId_ = newChatId;

    const int prevSize = messageModelItems_.size();
    messageModelItems_.clear();
    lastDate_ = QDate{};

    emit dataChanged(index(0, 0), index(prevSize, 0));
}

void MessageListModel::onMessageAdded(const Message &message)
{
    if (chatId_ != message.chatId())
        return;

    const int row = messageModelItems_.count();
    beginInsertRows(QModelIndex(), row, row);
    addMessage(message);
    endInsertRows();
}

void MessageListModel::addMessage(const Message &message)
{
    if (lastDate_ != message.createdAt().date()) {
        lastDate_ = message.createdAt().date();
        messageModelItems_.append(MessageModelItemPtr(new DateSeparatorItem{message.createdAt().date()}));
    }
    messageModelItems_.append(MessageItem::fromMessage(message));
}
