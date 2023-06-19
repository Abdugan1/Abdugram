#ifndef USERSTABLE_H
#define USERSTABLE_H

#include "SqlClient_global.h"

class QDateTime;

class User;

class SQLCLIENT_EXPORT UsersTable
{
public:
    static bool addOrIgnoreUser(const User &user);

    static User getUserById(int userId);

    static int lastInsertedId();

    static QDateTime getLastUpdatedAt();

private:
    explicit UsersTable() = default;

    static int lastInsertedId_;
};

#endif // USERSTABLE_H
