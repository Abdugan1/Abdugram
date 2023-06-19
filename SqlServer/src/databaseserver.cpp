#include "databaseserver.h"

#include <sql_common/functions.h>
#include <sql_common/data_structures/user.h>
#include <sql_common/data_structures/chat.h>
#include <sql_common/data_structures/chatuser.h>
#include <sql_common/data_structures/message.h>

#include "userstable.h"
#include "chatstable.h"
#include "chatuserstable.h"
#include "messagestable.h"

#include <QDir>
#include <QDirIterator>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

const QString HostName = "localhost";
const QString DbName   = "abdugram";
const QString UserName = "abdu";
const QString Password = "AbduganiYerzhanov002@!";

DatabaseServer *DatabaseServer::instance()
{
    static DatabaseServer self;
    return &self;
}

void DatabaseServer::connectToDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName(HostName);
    db.setDatabaseName(DbName);
    db.setUserName(UserName);
    db.setPassword(Password);

    if (db.open())
        createTables();
    else
        qFatal(qPrintable("Couldn't open database!" + db.lastError().text()));
}

bool DatabaseServer::isUsernameExists(const QString &username)
{
    return UsersTable::isUsernameExists(username);
}

bool DatabaseServer::isUserExists(const QString &username, const QString &password)
{
    return UsersTable::isUserExists(username, password);
}

bool DatabaseServer::addUser(const User &user, const QString &password)
{
    return UsersTable::addUser(user, password);
}

int DatabaseServer::getUserIdByUsername(const QString &username)
{
    return UsersTable::getUserIdByUsername(username);
}

User DatabaseServer::getUserById(int userId)
{
    return UsersTable::getUserById(userId);
}

QList<User> DatabaseServer::getUsersByLikeSearch(const QString &likeSearch)
{
    return UsersTable::getUsersByLikeSearch(likeSearch);
}

QList<User> DatabaseServer::getUpdatedUsersForUser(int userId, const QDateTime &lastUpdatedAt)
{
    return UsersTable::getUpdatedUsersForUser(userId, lastUpdatedAt);
}

bool DatabaseServer::addChat(const Chat &chat, const QList<ChatUser> &chatUsers)
{
    const bool success = executeTransaction([&]() {
        if (!ChatsTable::addChat(chat)) {
            return false;
        }
        const int addedChatId = ChatsTable::lastInsertedId();
        qDebug() << "addedChatId in DatabaseServer:" << addedChatId;
        if (!ChatUsersTable::addUsersToChat(addedChatId, chatUsers)) {
            return false;
        }

        return true;
    });

    return success;
}

Chat DatabaseServer::getChatById(int id)
{
    return ChatsTable::getChatById(id);
}

QList<ChatUser> DatabaseServer::getChatUsers(int chatId)
{
    return ChatUsersTable::getChatUsers(chatId);
}

bool DatabaseServer::addMessage(const Message &message)
{
    return MessagesTable::addMessage(message);
}

Message DatabaseServer::getMessageById(int id)
{
    return MessagesTable::getMessageById(id);
}

int DatabaseServer::lastInsertedId(Tables table)
{
    switch (table) {
    case Tables::Users:     return UsersTable::lastInsertedId();    break;
    case Tables::Chats:     return ChatsTable::lastInsertedId();    break;
    case Tables::ChatUsers: break;
    case Tables::Messages:  return MessagesTable::lastInsertedId(); break;
    }

    return 0;
}

void DatabaseServer::createTables()
{
    QString fileName("./.sql/create/create.sql");
    QSqlQuery createQuery{readFullFile(fileName)};
    if (!createQuery.exec()) {
        qFatal(qPrintable("Couldn't create tables!" + createQuery.lastError().text()));
    }
}
