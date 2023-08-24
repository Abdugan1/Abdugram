#ifndef MESSAGEREADS_H
#define MESSAGEREADS_H

#include "../SqlCommon_global.h"

#include <QDateTime>

class QSqlRecord;
class QDataStream;

class SQLCOMMON_EXPORT MessageRead
{
public:
    explicit MessageRead();

    int userId() const;
    void setUserId(int newUserId);

    int messageId() const;
    void setMessageId(int newMessageId);

    QDateTime readTime() const;
    void setReadTime(const QDateTime &newReadTime);

    static MessageRead fromSqlRecord(const QSqlRecord &record);

    QDateTime createdAt() const;
    void setCreatedAt(const QDateTime &newCreatedAt);

    QDateTime updatedAt() const;
    void setUpdatedAt(const QDateTime &newUpdatedAt);

    SQLCOMMON_EXPORT friend QDataStream &operator<<(QDataStream &out, const MessageRead &messageReads);
    SQLCOMMON_EXPORT friend QDataStream &operator>>(QDataStream &in, MessageRead &messageReads);

private:
    int userId_    = -1;
    int messageId_ = -1;
    QDateTime readTime_;
    QDateTime createdAt_;
    QDateTime updatedAt_;
};

#endif // MESSAGEREADS_H
