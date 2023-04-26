#include "userstable.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

#include <sql_common/functions.h>

#include <data_structures/user.h>

UsersTable::UsersTable()
{

}

bool UsersTable::isUsernameExists(const QString &username)
{
    const QString query = readFullFile("./.sql/users/count_of_username.sql");

    QSqlQuery usernameCountQuery;
    usernameCountQuery.prepare(query.trimmed());
    usernameCountQuery.bindValue(":username", username);

    if (!usernameCountQuery.exec() || !usernameCountQuery.first()) {
        qCritical() << "Couldn't execute query:" << usernameCountQuery.executedQuery()
                    << "error:" << usernameCountQuery.lastError().text();
        return true; // true, because if false, the UsersTable::addUser will caalled. So should return something else???
    }
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

    if (!addUserQuery.exec()) {
        qWarning() << "Couldn't add user" << user.username() << addUserQuery.lastError().text();
    }
}

bool UsersTable::isUserExists(const QString &username, const QString &password)
{
    const QString query = readFullFile("./.sql/users/is_user_exists.sql");

    QSqlQuery isUserExistsQuery;
    isUserExistsQuery.prepare(query);
    isUserExistsQuery.bindValue(":username", username);
    isUserExistsQuery.bindValue(":password", password);

    if (!isUserExistsQuery.exec() || !isUserExistsQuery.first()) {
        qCritical() << "Couldn't execute query:" << isUserExistsQuery.executedQuery()
                    << "error:" << isUserExistsQuery.lastError().text();
        return false; // Should return something else???
    }

    return isUserExistsQuery.value(0).toBool();
}
