#ifndef MESSAGE_H
#define MESSAGE_H

#include "API_global.h"
#include <QString>
#include <QDateTime>
#include <QObject> // for Q_GADGET

class API_EXPORT Message
{
    Q_GADGET
    Q_PROPERTY(int id READ id WRITE setId)
    Q_PROPERTY(int senderId READ senderId WRITE setSenderId)
    Q_PROPERTY(int conversationId READ conversationId WRITE setConversationId)
public:
    Message();

    int id() const;
    void setId(int newId);

    int senderId() const;
    void setSenderId(int newSenderId);

    int conversationId() const;
    void setConversationId(int newConversationId);

    const QString &text() const;
    void setText(const QString &newText);

    const QDateTime &createdAt() const;
    void setCreatedAt(const QDateTime &newCreatedAt);

    const QDateTime &updatedAt() const;
    void setUpdatedAt(const QDateTime &newUpdatedAt);

private:
    int id_             = -1;
    int senderId_       = -1;
    int conversationId_ = -1;
    QString text_;
    QDateTime createdAt_;
    QDateTime updatedAt_;
};

#endif // MESSAGE_H
