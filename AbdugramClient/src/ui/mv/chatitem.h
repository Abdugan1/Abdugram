#ifndef CHATITEM_H
#define CHATITEM_H

#include <QString>
#include <QDateTime>
#include <QUrl>

class ChatItem
{
public:
    explicit ChatItem();

    QUrl avatar() const;
    void setAvatar(const QUrl &newAvatar);

    QString chatName() const;
    void setChatName(const QString &newChatName);

    QString lastMessage() const;
    void setLastMessage(const QString &newLastMessage);

    QDateTime messageDate() const;
    void setMessageDate(const QDateTime &newMessageDate);

private:
    QUrl avatar_;
    QString chatName_;
    QString lastMessage_;
    QDateTime messageDate_;
};

#endif // CHATITEM_H
