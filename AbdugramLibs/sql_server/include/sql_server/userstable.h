#ifndef USERSTABLE_H
#define USERSTABLE_H

#include "SqlServer_global.h"

#include <QString>
#include <QDateTime>

class User;

class SQLSERVER_EXPORT UsersTable
{
public:
    static bool isUsernameExists(const QString &username);

    static bool addUser(const User &user, const QString &password);

    static bool isUserExists(const QString &username, const QString &password);

    static QList<User> getUsersByLikeSearch(const QString &likeSearch, int ownId);

    static int getUserIdByUsername(const QString &username);

    static User getUserById(int id);

    static QList<User> getUnsyncUsers(int userId, const QDateTime &lastUpdatedAt);

    static int lastInsertedId();

private:
    explicit UsersTable() = default;

    static int lastInsertedId_;
};

#endif // USERSTABLE_H
