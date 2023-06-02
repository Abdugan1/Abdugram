#ifndef USER_H
#define USER_H

#include "../SqlCommon_global.h"
#include <QString>
#include <QDateTime>

class QSqlRecord;

class SQLCOMMON_EXPORT User
{
public:
    explicit User();

    int id() const;
    void setId(int newId);

    QString username() const;
    void setUsername(const QString &newUsername);

    QString firstName() const;
    void setFirstName(const QString &newFirstName);

    QString lastName() const;
    void setLastName(const QString &newLastName);

    QString email() const;
    void setEmail(const QString &newEmail);

    QString phone() const;
    void setPhone(const QString &newPhone);

    QString avatarUrl() const;
    void setAvatarUrl(const QString &newAvatarUrl);

    QDateTime createdAt() const;
    void setCreatedAt(const QDateTime &newCreatedAt);

    QDateTime updatedAt() const;
    void setUpdatedAt(const QDateTime &newUpdatedAt);

    QDateTime lastTimeOnline() const;
    void setLastTimeOnline(const QDateTime &newLastTimeOnline);

    bool isOnline() const;
    void setIsOnline(bool newIsOnline);

    bool isDeleted() const;
    void setIsDeleted(bool newIsDeleted);

    static User fromSqlRecord(const QSqlRecord &record);

private:
    int       id_ = -1;

    QString   username_;
    QString   firstName_;
    QString   lastName_;
    QString   email_;
    QString   phone_;
    QString   avatarUrl_;

    QDateTime createdAt_;
    QDateTime updatedAt_;

    QDateTime lastTimeOnline_;
    bool      isOnline_  = false;
    bool      isDeleted_ = false;

    friend QDataStream &operator<<(QDataStream &out, const User &user);
    friend QDataStream &operator>>(QDataStream &in, User &user);
};

QDataStream &operator<<(QDataStream &out, const User &user);
QDataStream &operator>>(QDataStream &in, User &user);

#endif // USER_H
