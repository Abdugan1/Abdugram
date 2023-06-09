#ifndef USERSTABLE_H
#define USERSTABLE_H

#include "SqlClient_global.h"

class User;

class SQLCLIENT_EXPORT UsersTable
{
public:
    static bool addOrIgnoreUser(const User &user);

    static User getUserById(int userId);

private:
    explicit UsersTable() = default;
};

#endif // USERSTABLE_H
