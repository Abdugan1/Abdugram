#ifndef USERSTABLE_H
#define USERSTABLE_H

#include <QString>
#include <QDateTime>

class User;

class UsersTable
{
public:
    explicit UsersTable();

    static bool isUsernameExists(const QString &username);

    static void addUser(const User &user, const QString &password);

    static bool isUserExists(const QString &username, const QString &password);

    static QList<User> getUsers(const QString &likeSearch);
};

#endif // USERSTABLE_H
