#ifndef CHATLISTMODEL_H
#define CHATLISTMODEL_H

#include <QAbstractListModel>

#include <memory>

class User;
class Chat;
class ChatUser;

class ChatModelItem;

using ChatModelItemPtr = std::shared_ptr<ChatModelItem>;

class ChatListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    using ChatModelItems = QVector<ChatModelItemPtr>;

    explicit ChatListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void addChatItem(const ChatModelItemPtr &item);
    ChatModelItemPtr chatItem(int row) const;

    void setChatItems(const QList<ChatModelItemPtr> &chatItems);

private:
    ChatModelItems chatItems_;
};

#endif // CHATLISTMODEL_H
