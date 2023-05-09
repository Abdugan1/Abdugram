#ifndef MESSAGELISTMODEL_H
#define MESSAGELISTMODEL_H

#include <QAbstractListModel>

#include "messageitem.h"

class ChatItem;

class MessageListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        Text = Qt::UserRole + 1,
        DateTime,
        SenderId,
    };

    explicit MessageListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    bool isEmpty() const;


private:
    using MessageItems = QVector<MessageItem>;
    MessageItems messageItems_;
};

#endif // MESSAGELISTMODEL_H
