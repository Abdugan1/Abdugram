#include "chatlistmodel.h"

#include <QModelIndex>

ChatListModel::ChatListModel(QObject *parent)
    : QAbstractListModel{parent}
{
    ChatItem abdugani;
    abdugani.setChatName("Abdugan1");
    abdugani.setLastMessage("Last message is presented here");
    abdugani.setMessageDate(QDateTime{QDate{2002, 05, 17}, QTime{9, 42}});

    ChatItem nurzhan;
    nurzhan.setChatName("Nurzhan");
    nurzhan.setLastMessage("Last message is presented here");
    nurzhan.setMessageDate(QDateTime{QDate{2002, 05, 17}, QTime{9, 43}});

    ChatItem biko;
    biko.setChatName("Biko");
    biko.setLastMessage("Last message is presented here");
    biko.setMessageDate(QDateTime{QDate{2002, 05, 17}, QTime{9, 43}});

    ChatItem para;
    para.setChatName("Para");
    para.setLastMessage("Last message is presented here");
    para.setMessageDate(QDateTime{QDate{2002, 05, 17}, QTime{9, 43}});

    ChatItem yqyl;
    yqyl.setChatName("Yqyl");
    yqyl.setLastMessage("Last message is presented here");
    yqyl.setMessageDate(QDateTime{QDate{2002, 05, 17}, QTime{9, 43}});

//    addChatItem(abdugani);
//    addChatItem(nurzhan);
//    addChatItem(biko);
//    addChatItem(para);
//    addChatItem(yqyl);
}

int ChatListModel::rowCount(const QModelIndex &) const
{
    return chatItems_.count();
}

QVariant ChatListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant{};
    const ChatItem &chatItem = chatItems_.at(index.row());
    switch (role) {
    case Roles::Avatar:      return chatItem.avatar();      break;
    case Roles::ChatName:    return chatItem.chatName();    break;
    case Roles::LastMessage: return chatItem.lastMessage(); break;
    case Roles::MessageDate: return chatItem.messageDate(); break;
    }

    return QVariant{};
}

void ChatListModel::addChatItem(const ChatItem &item)
{
    const int row = chatItems_.count();
    beginInsertRows(QModelIndex(), row, row);
    chatItems_.append(item);
    endInsertRows();
}

void ChatListModel::clear()
{
    int oldSize = chatItems_.size();
    chatItems_.clear();
    if (oldSize != chatItems_.size())
        emit dataChanged(this->index(0, 0), this->index(oldSize, 0));
}
