#ifndef CHATLISTMODEL_H
#define CHATLISTMODEL_H

#include <QAbstractListModel>

#include <memory>

class User;
class Chat;
class ChatUser;

class ChatModelItem;
class ChatItem;
class FoundUserItem;

using ChatModelItemPtr = std::shared_ptr<ChatModelItem>;
using ChatItemPtr = std::shared_ptr<ChatItem>;
using FoundUserItemPtr = std::shared_ptr<FoundUserItem>;

class ChatListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    using ChatModelItems = QVector<ChatModelItemPtr>;

    explicit ChatListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void addChatItem(const ChatItemPtr &item);

    ChatModelItemPtr chatModelItem(int row) const;

    int rowByChatId(int id) const;

    void setChatItems(const QList<ChatItemPtr> &chatItems);
    void addFoundUserItems(const QList<FoundUserItemPtr> &foundUsers);

private:
    ChatModelItems chatModelItems_;
};

#endif // CHATLISTMODEL_H
