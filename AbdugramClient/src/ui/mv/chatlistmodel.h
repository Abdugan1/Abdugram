#ifndef CHATLISTMODEL_H
#define CHATLISTMODEL_H

#include <QAbstractListModel>

#include "chatitem.h"

class User;

class ChatListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        Avatar = Qt::UserRole + 1,
        ChatName,
        LastMessage,
        MessageDate
    };

    explicit ChatListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    void addChatItem(const ChatItem &item);
    ChatItem chatItem(int row) const;

    void setUserList(const QList<User> &userList);

private:
    using ChatItems = QVector<ChatItem>;
    ChatItems chatItems_;
};

#endif // CHATLISTMODEL_H
