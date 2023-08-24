#ifndef MESSAGE_H
#define MESSAGE_H

#include "../SqlCommon_global.h"

#include <QDateTime>

class QSqlRecord;

class SQLCOMMON_EXPORT Message
{
public:
    explicit Message();

    int id() const;
    void setId(int newId);

    int chatId() const;
    void setChatId(int newChatId);

    int senderId() const;
    void setSenderId(int newSenderId);

    int replyToId() const;
    void setReplyToId(int newReplyToId);

    QString text() const;
    void setText(const QString &newText);

    bool isEdited() const;
    void setIsEdited(bool newIsEdited);

    QDateTime createdAt() const;
    void setCreatedAt(const QDateTime &newCreatedAt);

    QDateTime updatedAt() const;
    void setUpdatedAt(const QDateTime &newUpdatedAt);

    static Message fromSqlRecord(const QSqlRecord &record);

    SQLCOMMON_EXPORT friend QDataStream &operator<<(QDataStream &out, const Message &message);
    SQLCOMMON_EXPORT friend QDataStream &operator>>(QDataStream &in, Message &message);

    bool isRead() const;
    void setIsRead(bool newIsRead);

private:
    int id_ = -1;
    int chatId_ = -1;
    int senderId_ = -1;
    int replyToId_ = -1;
    QString text_;
    bool isEdited_ = false;
    bool isRead_ = false;
    QDateTime createdAt_;
    QDateTime updatedAt_;
};

#endif // MESSAGE_H
