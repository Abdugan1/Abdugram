#ifndef MESSAGELISTMODEL_H
#define MESSAGELISTMODEL_H

#include <QAbstractListModel>
#include <QDate>

#include <memory>

class MessageModelItem;

class Message;

class MessageListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum class Roles {
        Type = Qt::UserRole + 1,
    };

    explicit MessageListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    bool isEmpty() const;

    int chatId() const;
    void setChatId(int newChatId);
    void setChatIdWithoutSelect(int newChatId);

public slots:
    void onMessageAdded(const Message &message);

private:
    void addMessage(const Message &message);

private:
    using MessageModelItemPtr = std::shared_ptr<MessageModelItem>;
    using MessageModelItems = QVector<MessageModelItemPtr>;
    MessageModelItems messageModelItems_;

    int chatId_ = -1;

    QDate lastDate_;
};

#endif // MESSAGELISTMODEL_H
