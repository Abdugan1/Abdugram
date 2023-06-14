#include "databaseclient.h"

#include "userstable.h"
#include "chatstable.h"
#include "chatuserstable.h"
#include "messagestable.h"

#include <sql_common/data_structures/user.h>
#include <sql_common/data_structures/chat.h>
#include <sql_common/data_structures/chatuser.h>
#include <sql_common/data_structures/message.h>
#include <sql_common/functions.h>

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

const QString DbName = "abdugram";

DatabaseClient *DatabaseClient::instance()
{
    static DatabaseClient self;
    return &self;
}

void DatabaseClient::connectToDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(".sql/" + DbName);

    if (db.open())
        createTables();
    else
        qFatal(qPrintable("Couldn't open database!" + db.lastError().text()));
}

bool DatabaseClient::addOrIgnoreUser(const User &user)
{
    bool success = UsersTable::addOrIgnoreUser(user);

    if (success)
        emit userAdded(user);

    return success;
}

bool DatabaseClient::addChat(Chat chat, const QList<ChatUser> &chatUsers, int ownUserId)
{
    bool success = executeTransaction([&]() {
        if (chat.type() == Chat::Type::Private) {
            auto it = std::find_if(chatUsers.begin(), chatUsers.end(), [&](const ChatUser &chatUser) {
                return chatUser.userId() != ownUserId;
            });
            chat.setName(UsersTable::getUserById(it->userId()).username());
        }

        if (!ChatsTable::addChat(chat))
            return false;

        for (const auto &chatUser : chatUsers) {
            if (!ChatUsersTable::addUserToChat(chatUser, chat.id()))
                return false;
        }

        return true;
    });

    if (success)
        emit chatAdded(chat);
}

bool DatabaseClient::addMessage(const Message &message)
{
    bool success = MessagesTable::addMessage(message);

    if (success)
        emit messageAdded(message);

    return success;
}

QList<Message> DatabaseClient::getMessages(int chatId)
{
    return MessagesTable::getMessages(chatId);
}

void DatabaseClient::createTables()
{
    QSqlQuery enableForeignKeys{"PRAGMA foreign_keys = ON;"};

    if (!enableForeignKeys.exec()) {
        qFatal(qPrintable("Couldn't enable keys!" + enableForeignKeys.lastError().text()));
    }

    QString fileName("./.sql/create/create.sql");
    QString queries = readFullFile(fileName);

    QStringList queryList = queries.split(";");
    for (QString query : queryList) {
        query = query.trimmed();
        if (query.isEmpty())
            continue;
        QSqlQuery createQuery{query};
        if (!createQuery.exec()) {
            qFatal(qPrintable("Couldn't execute query!" + createQuery.lastError().text()));
        }
    }
}
