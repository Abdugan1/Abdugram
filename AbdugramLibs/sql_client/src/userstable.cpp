#include "userstable.h"
#include "sqlquery.h"

#include <sql_common/functions.h>
#include <sql_common/data_structures/user.h>

#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

int UsersTable::lastInsertedId_ = -1;

bool UsersTable::addOrUpdateUser(const User &user)
{
    const QString query = "INSERT INTO users(id, username, first_name, email, phone, avatar_url, is_online, last_time_online, url_to_profile, created_at, updated_at, deleted_at) "
                          "VALUES(:id, :username, :first_name, :email, :phone, :avatar_url, :is_online, :last_time_online, :url_to_profile, :created_at, :updated_at, :deleted_at) "
                          "ON CONFLICT(id) DO UPDATE SET "
                          "     username = excluded.username, "
                          "     first_name = excluded.first_name, "
                          "     email = excluded.email, "
                          "     phone = excluded.phone, "
                          "     avatar_url = excluded.avatar_url, "
                          "     is_online = excluded.is_online, "
                          "     last_time_online = excluded.last_time_online, "
                          "     url_to_profile = excluded.url_to_profile, "
                          "     created_at = excluded.created_at, "
                          "     updated_at = excluded.updated_at, "
                          "     deleted_at = excluded.deleted_at;";

    SqlQuery addUserQuery;
    addUserQuery.prepare(query);
    addUserQuery.bindValue(":id", user.id());
    addUserQuery.bindValue(":username", user.username());
    addUserQuery.bindValue(":first_name", user.firstName());
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
    const QString query = "SELECT * FROM users WHERE id = :id;";

    SqlQuery getUserByIdQuery;
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

