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

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    bool isEmpty() const;

    int chatId() const;
    void setChatId(int newChatId);
    void setChatIdWithoutSelect(int newChatId);

signals:
    void messageAdded(const Message &message);

public slots:
    void onMessageAdded(const Message &message);
    void onMessagesUpdated(const QList<Message> &updatedMessages);

private:
    void addMessage(const Message &message);

    void clear();

private:
    using MessageModelItemPtr = std::shared_ptr<MessageModelItem>;
    using MessageModelItems = QVector<MessageModelItemPtr>;

    QHash<int, int> messageIdToRow_;
    MessageModelItems messageModelItems_;

    int chatId_ = -1;

    QDate lastDate_;
};

#endif // MESSAGELISTMODEL_H
