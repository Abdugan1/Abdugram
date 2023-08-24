#include "databaseserver.h"

#include "userstable.h"
#include "chatstable.h"
#include "chatuserstable.h"
#include "messagestable.h"
#include "messagereadstable.h"

#include <sql_common/functions.h>
#include <sql_common/data_structures/user.h>
#include <sql_common/data_structures/chat.h>
#include <sql_common/data_structures/chatuser.h>
#include <sql_common/data_structures/message.h>
#include <sql_common/data_structures/messagereads.h>

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

QList<User> DatabaseServer::getUsersByLikeSearch(const QString &likeSearch, int ownId)
{
    return UsersTable::getUsersByLikeSearch(likeSearch, ownId);
}

QList<User> DatabaseServer::getUnsyncUsers(int userId, const QDateTime &lastUpdatedAt)
{
    return UsersTable::getUnsyncUsers(userId, lastUpdatedAt);
}

bool DatabaseServer::addChat(const Chat &chat, const QList<ChatUser> &chatUsers)
{
    const bool success = executeTransaction(QSqlDatabase::database(), [&]() {
        if (!ChatsTable::addChat(chat)) {
            return false;
        }
        const int addedChatId = ChatsTable::lastInsertedId();
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

QList<Chat> DatabaseServer::getUnsyncChats(int userId, const QDateTime &lastUpdatedAt)
{
    return ChatsTable::getUnsyncChats(userId, lastUpdatedAt);
}

QList<ChatUser> DatabaseServer::getChatUsers(int chatId)
{
    return ChatUsersTable::getChatUsers(chatId);
}

QList<ChatUser> DatabaseServer::getUnsyncChatUsers(int userId, int chatId, const QDateTime &lastUpdatedAt)
{
    return ChatUsersTable::getUnsyncChatUsers(userId, chatId, lastUpdatedAt);
}

bool DatabaseServer::addMessage(const Message &message)
{
    return MessagesTable::addMessage(message);
}

Message DatabaseServer::getMessageById(int id)
{
    return MessagesTable::getMessageById(id);
}

QList<Message> DatabaseServer::getUnsyncMessages(int userId, const QDateTime &lastUpdatedAt)
{
    return MessagesTable::getUnsyncMessages(userId, lastUpdatedAt);
}

bool DatabaseServer::setIsReadOfMessageToTrue(int messageId)
{
    return MessagesTable::setIsReadOfMessageToTrue(messageId);
}

bool DatabaseServer::addMessageReads(const QList<MessageRead> &messageReads)
{
    const bool success = executeTransaction(QSqlDatabase::database(), [this, &messageReads]()->bool {
        for (const auto &messageRead : messageReads) {
            if (!MessageReadsTable::addMessageReads(messageRead)) {
                return false;
            }
        }
        return true;
    });

    return success;
}

QList<MessageRead> DatabaseServer::getUnsyncMessageReads(int userId, const QDateTime &lastUpdatedAt)
{
    return MessageReadsTable::getUnsyncMessageReads(userId, lastUpdatedAt);
}

int DatabaseServer::lastInsertedId(Tables table)
{
    switch (table) {
    case Tables::Users:        return UsersTable::lastInsertedId();    break;
    case Tables::Chats:        return ChatsTable::lastInsertedId();    break;
    case Tables::ChatUsers:    break;
    case Tables::Messages:     return MessagesTable::lastInsertedId(); break;
    case Tables::MessageReads: return MessagesTable::lastInsertedId(); break;
    }

    return 0;
}

int DatabaseServer::getCountOfMessageReadsOfSpecificMessage(int messageId)
{
    QSqlQuery messageReadsCountQuery;
    messageReadsCountQuery.prepare("SELECT COUNT(*) "
                                   "FROM message_reads "
                                   "WHERE message_id = :message_id;");
    messageReadsCountQuery.bindValue(":message_id", messageId);
    if (!executeQuery(messageReadsCountQuery, ErrorImportance::Warning)) {
        return -1;
    }

    messageReadsCountQuery.first();
    return messageReadsCountQuery.value(0).toInt();
}

void DatabaseServer::createTables()
{
    QString fileName("./.sql/create/create.sql");
    QSqlQuery createQuery{readFullFile(fileName)};
    if (!createQuery.exec()) {
        qFatal(qPrintable("Couldn't create tables!" + createQuery.lastError().text()));
    }
}
