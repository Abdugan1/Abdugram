#ifndef CHATLISTMODEL_H
#define CHATLISTMODEL_H

#include <QAbstractListModel>

#include <memory>

#include "chatitem.h"

class User;
class Chat;
class ChatUser;

class ChatListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    using ChatItems   = QVector<ChatItemPtr>;

    enum Roles {
        Avatar = Qt::UserRole + 1,
        ChatName,
        LastMessage,
        MessageDate
    };

    explicit ChatListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    void addChatItem(const ChatItemPtr &item);
    ChatItemPtr chatItem(int row) const;

    void setChatItems(const ChatItems &chatItems);

    bool isChatItemExists(const ChatItemPtr &chatItem) const;

private:
    ChatItems chatItems_;
};

#endif // CHATLISTMODEL_H
