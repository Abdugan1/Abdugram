#include "ui/mv/messagelistmodel.h"
#include "ui/mv/messageitem.h"
#include "ui/mv/dateseparatoritem.h"

#include <sql_client/databaseclient.h>

#include <sql_common/data_structures/message.h>

#include <QDebug>

MessageListModel::MessageListModel(QObject *parent)
    : QAbstractListModel{parent}
{
    connect(database(), &DatabaseClient::messageAdded,    this, &MessageListModel::onMessageAdded);
    connect(database(), &DatabaseClient::messagesUpdated, this, &MessageListModel::onMessagesUpdated);
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
    clear();

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
    clear();

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

void MessageListModel::onMessagesUpdated(const QList<Message> &updatedMessages)
{
    for (const auto &message : updatedMessages) {
        const int row = messageIdToRow_.value(message.id());
        auto messageItem = messageModelItems_[row];
        messageItem->setData(MessageItem::MessageId,message.id());
        messageItem->setData(MessageItem::SenderId, message.senderId());
        messageItem->setData(MessageItem::Text,     message.text());
        messageItem->setData(MessageItem::DateTime, message.createdAt());
        messageItem->setData(MessageItem::IsRead,   message.isRead());
        messageItem->setData(MessageItem::IsEdited, message.isEdited());
    }
}

void MessageListModel::addMessage(const Message &message)
{
    if (lastDate_ != message.createdAt().date()) {
        lastDate_ = message.createdAt().date();
        messageModelItems_.append(MessageModelItemPtr(new DateSeparatorItem{message.createdAt().date()}));
    }
    messageModelItems_.append(MessageItem::fromMessage(message));
    messageIdToRow_[message.id()] = messageModelItems_.size() - 1;
}

void MessageListModel::clear()
{
    messageModelItems_.clear();
    messageIdToRow_.clear();
    lastDate_ = QDate{};
}
