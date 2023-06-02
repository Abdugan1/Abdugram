#ifndef CHATUSER_H
#define CHATUSER_H

#include "../SqlCommon_global.h"

#include <QDateTime>

class QSqlRecord;

class SQLCOMMON_EXPORT ChatUser
{
public:
    enum Role {
        Unknown,
        Owner,
        Admin,
        User,
    };
    explicit ChatUser();

    int chatId() const;
    void setChatId(int newChatId);

    int userId() const;
    void setUserId(int newUserId);

    Role role() const;
    void setRole(Role newRole);

    QDateTime joinedAt() const;
    void setJoinedAt(const QDateTime &newJoinedAt);

    QDateTime leftAt() const;
    void setLeftAt(const QDateTime &newLeftAt);

    bool isValid() const;

    static QString roleToString(Role role);
    static Role    stringToRole(const QString &str);

    static ChatUser fromSqlRecord(const QSqlRecord &record);

private:
    int chatId_ = -1;
    int userId_ = -1;
    Role role_  = User;
    QDateTime joinedAt_;
    QDateTime leftAt_;

    friend QDataStream &operator<<(QDataStream &out, const ChatUser &chatUser);
    friend QDataStream &operator>>(QDataStream &in, ChatUser &chatUser);

};

QDataStream &operator<<(QDataStream &out, const ChatUser &chatUser);
QDataStream &operator>>(QDataStream &in, ChatUser &chatUser);


#endif // CHATUSER_H
