#include "userstable.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

#include <sql_common/functions.h>
#include <sql_common/data_structures/user.h>

bool UsersTable::isUsernameExists(const QString &username)
{
    const QString query = readFullFile("./.sql/users/count_of_username.sql");

    QSqlQuery usernameCountQuery;
    usernameCountQuery.prepare(query.trimmed());
    usernameCountQuery.bindValue(":username", username);

    if (!executeQuery(usernameCountQuery, ErrorImportance::Critical)) {
        return true; // true, because if false, the UsersTable::addUser will called.
                     //So should return something else???
    }

    usernameCountQuery.first();
    return usernameCountQuery.value(0).toBool();
}

void UsersTable::addUser(const User &user, const QString &password)
{
    const QString query = readFullFile("./.sql/users/add_user.sql");

    QSqlQuery addUserQuery;
    addUserQuery.prepare(query);
    addUserQuery.bindValue(":first_name",   user.firstName());
    addUserQuery.bindValue(":last_name",    user.lastName() );
    addUserQuery.bindValue(":username",     user.username() );
    addUserQuery.bindValue(":email",        user.email()    );
    addUserQuery.bindValue(":phone",        user.phone()    );
    addUserQuery.bindValue(":password",     password        );

    executeQuery(addUserQuery, ErrorImportance::Warning);
}

bool UsersTable::isUserExists(const QString &username, const QString &password)
{
    const QString query = readFullFile("./.sql/users/is_user_exists.sql");

    QSqlQuery isUserExistsQuery;
    isUserExistsQuery.prepare(query);
    isUserExistsQuery.bindValue(":username", username);
    isUserExistsQuery.bindValue(":password", password);

    if (!executeQuery(isUserExistsQuery, ErrorImportance::Critical)) {
        return false; // TODO: Should return something else???
    }

    isUserExistsQuery.first();
    return isUserExistsQuery.value(0).toBool();
}

QList<User> UsersTable::getUsersByLikeSearch(const QString &likeSearch)
{
    const QString query = readFullFile("./.sql/users/search.sql");

    QSqlQuery searchUsersQuery;
    searchUsersQuery.prepare(query);
    searchUsersQuery.bindValue(":like_search", likeSearch);

    if (!executeQuery(searchUsersQuery, ErrorImportance::Critical)) {
        return QList<User>{};
    }

    QList<User> users;
    while (searchUsersQuery.next())
        users.append(User::fromSqlRecord(searchUsersQuery.record()));

    return users;
}

int UsersTable::getUserIdByUsername(const QString &username)
{
    const QString query = readFullFile("./.sql/users/get_user_id_by_username.sql");

    QSqlQuery getUserIdQuery;
    getUserIdQuery.prepare(query);
    getUserIdQuery.bindValue(":username", username);

    if (!executeQuery(getUserIdQuery, ErrorImportance::Critical)) {
        return -1;
    }

    getUserIdQuery.first();
    return getUserIdQuery.value(0).toInt();
}

User UsersTable::getUserById(int id)
{
    const QString query = readFullFile("./sql/users/get_user_by_id.sql");

    QSqlQuery getUserByIdQuery;
    getUserByIdQuery.prepare(query);
    getUserByIdQuery.bindValue(":user_id", id);

    if (!executeQuery(getUserByIdQuery, ErrorImportance::Warning)) {
        return User{};
    }

    getUserByIdQuery.first();
    return User::fromSqlRecord(getUserByIdQuery.record());
}
