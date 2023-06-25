#ifndef MESSAGEITEM_H
#define MESSAGEITEM_H

#include <QString>
#include <QDateTime>

class Message;

class MessageItem
{
public:
    explicit MessageItem();

    int senderId() const;
    void setSenderId(int newSenderId);

    QString text() const;
    void setText(const QString &newText);

    QDateTime dateTime() const;
    void setDateTime(const QDateTime &newDateTime);

    static MessageItem fromMessage(const Message &message);

private:
    int senderId_ = -1;
    QString text_;
    QDateTime dateTime_;
};

#endif // MESSAGEITEM_H
