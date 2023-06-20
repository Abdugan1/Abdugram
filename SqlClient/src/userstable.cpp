#include "userstable.h"

#include <sql_common/functions.h>
#include <sql_common/data_structures/user.h>

#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

int UsersTable::lastInsertedId_ = -1;

bool UsersTable::addOrUpdateUser(const User &user)
{
    const QString query = readFullFile("./.sql/users/add_or_update_user.sql");

    QSqlQuery addUserQuery;
    addUserQuery.prepare(query);
    addUserQuery.bindValue(":id", user.id());
    addUserQuery.bindValue(":username", user.username());
    addUserQuery.bindValue(":first_name", user.firstName());
    addUserQuery.bindValue(":last_name", user.lastName());
    addUserQuery.bindValue(":email", user.email());
    addUserQuery.bindValue(":phone", user.phone());
    addUserQuery.bindValue(":avatar_url", user.avatarUrl());
    addUserQuery.bindValue(":is_online", user.isOnline());
    addUserQuery.bindValue(":last_time_online", user.lastTimeOnline());
    addUserQuery.bindValue(":url_to_profile", user.urlToProfile());
    addUserQuery.bindValue(":created_at", user.createdAt());
    addUserQuery.bindValue(":updated_at", user.updatedAt());
    addUserQuery.bindValue(":deleted_at", user.deletedAt());

    const bool success = executeQuery(addUserQuery, ErrorImportance::Critical);

    lastInsertedId_ = addUserQuery.lastInsertId().toInt();
    return success;
}

User UsersTable::getUserById(int userId)
{
    const QString query = readFullFile("./.sql/users/get_user_by_id.sql");

    QSqlQuery getUserByIdQuery;
    getUserByIdQuery.prepare(query);
    getUserByIdQuery.bindValue(":id", userId);

    if (!executeQuery(getUserByIdQuery, ErrorImportance::Critical))
        return User{};

    getUserByIdQuery.first();
    return User::fromSqlRecord(getUserByIdQuery.record());
}

int UsersTable::lastInsertedId()
{
    return lastInsertedId_;
}

