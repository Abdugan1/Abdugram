#include "userstable.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

#include <sql_common/functions.h>
#include <sql_common/data_structures/user.h>

int UsersTable::lastInsertedId_ = -1;

bool UsersTable::isUsernameExists(const QString &username)
{
    const QString query = "SELECT COUNT(*) FROM users WHERE username = :username;";

    QSqlQuery usernameCountQuery;
    usernameCountQuery.prepare(query.trimmed());
    usernameCountQuery.bindValue(":username", username);

    executeQuery(usernameCountQuery, ErrorImportance::Fatal); // TODO: Do something else?
    usernameCountQuery.first();
    return usernameCountQuery.value(0).toBool();
}

bool UsersTable::addUser(const User &user, const QString &password)
{
    const QString query = "INSERT INTO users(first_name, last_name, username, password, email, phone) "
                          "VALUES(:first_name, :last_name, :username, :password, :email, :phone);";

    QSqlQuery addUserQuery;
    addUserQuery.prepare(query);
    addUserQuery.bindValue(":first_name",   user.firstName());
    addUserQuery.bindValue(":last_name",    user.lastName() );
    addUserQuery.bindValue(":username",     user.username() );
    addUserQuery.bindValue(":email",        user.email()    );
    addUserQuery.bindValue(":phone",        user.phone()    );
    addUserQuery.bindValue(":password",     password        );

    const bool success = executeQuery(addUserQuery, ErrorImportance::Warning);

    lastInsertedId_ = addUserQuery.lastInsertId().toInt();
    return success;
}

bool UsersTable::isUserExists(const QString &username, const QString &password)
{
    const QString query = "SELECT COUNT(*) FROM users WHERE (username=:username AND password=:password);";

    QSqlQuery isUserExistsQuery;
    isUserExistsQuery.prepare(query);
    isUserExistsQuery.bindValue(":username", username);
    isUserExistsQuery.bindValue(":password", password);

    executeQuery(isUserExistsQuery, ErrorImportance::Critical); // TODO: Do something else?
    isUserExistsQuery.first();
    return isUserExistsQuery.value(0).toBool();
}

QList<User> UsersTable::getUsersByLikeSearch(const QString &likeSearch)
{
    const QString query = "SELECT * FROM users WHERE username LIKE :like_search OR first_name LIKE :like_search;";

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
    const QString query = "SELECT id FROM users WHERE username = :username;";

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
    const QString query = "SELECT * FROM users WHERE id = :user_id;";

    QSqlQuery getUserByIdQuery;
    getUserByIdQuery.prepare(query);
    getUserByIdQuery.bindValue(":user_id", id);

    if (!executeQuery(getUserByIdQuery, ErrorImportance::Warning)) {
        return User{};
    }

    getUserByIdQuery.first();
    return User::fromSqlRecord(getUserByIdQuery.record());
}

QList<User> UsersTable::getUnsyncUsers(int userId, const QDateTime &lastUpdatedAt)
{
    const QString query = "SELECT u.* "
                          "FROM users u "
                          "JOIN chat_users cu ON cu.user_id = u.id "
                          "JOIN chats c ON c.id = cu.chat_id "
                          "WHERE c.id IN ( "
                          "SELECT chat_id "
                          "FROM chat_users "
                          "WHERE user_id = :user_id "
                          ") "
                          "AND u.updated_at >= :last_updated_at;";

    QSqlQuery getUsersQuery;
    getUsersQuery.setForwardOnly(true);
    getUsersQuery.prepare(query);
    getUsersQuery.bindValue(":user_id", userId);
    getUsersQuery.bindValue(":last_updated_at", lastUpdatedAt);

    if (!executeQuery(getUsersQuery, ErrorImportance::Critical)) {
        return QList<User>{};
    }

    QList<User> users;
    while (getUsersQuery.next()) {
        users.append(User::fromSqlRecord(getUsersQuery.record()));
    }

    return users;
}

int UsersTable::lastInsertedId()
{
    return lastInsertedId_;
}
