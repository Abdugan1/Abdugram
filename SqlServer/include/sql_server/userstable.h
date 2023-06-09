#ifndef USERSTABLE_H
#define USERSTABLE_H

#include <QString>
#include <QDateTime>

class User;

class UsersTable
{
public:
    static bool isUsernameExists(const QString &username);

    static void addUser(const User &user, const QString &password);

    static bool isUserExists(const QString &username, const QString &password);

    static QList<User> getUsersByLikeSearch(const QString &likeSearch);

    static int getUserIdByUsername(const QString &username);

    static User getUserById(int id);
};

#endif // USERSTABLE_H
