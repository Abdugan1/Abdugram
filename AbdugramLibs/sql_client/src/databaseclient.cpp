#include "databaseclient.h"
#include "sqlquery.h"
#include "database.h"

#include "userstable.h"
#include "chatstable.h"
#include "chatuserstable.h"
#include "messagestable.h"

#include <sql_common/data_structures/user.h>
#include <sql_common/data_structures/chat.h>
#include <sql_common/data_structures/chatuser.h>
#include <sql_common/data_structures/message.h>
#include <sql_common/functions.h>

#include <QSqlError>
#include <QMap>
#include <QThread>
#include <QDebug>

const QString DbName = "abdugram";

DatabaseClient *DatabaseClient::instance()
{
    static DatabaseClient self;
    return &self;
}

std::shared_ptr<SqlDatabase> DatabaseClient::threadDb()
{
    if (!threadDatabases_.hasLocalData()) {
        threadDatabases_.setLocalData(std::make_shared<SqlDatabase>());
    }
    auto db = threadDatabases_.localData();
    db->connect();
    return threadDatabases_.localData();
}

int DatabaseClient::ownId() const
{
    return ownId_;
}

void DatabaseClient::setOwnId(int ownId)
{
    ownId_ = ownId;
}

QDateTime DatabaseClient::getLastUpdatedAt(Tables table)
{
    static const QMap<Tables, QString> tableToString {
        {Tables::Users, "users"},
        {Tables::Chats, "chats"},
        {Tables::ChatUsers, "chat_users"},
        {Tables::Messages, "messages"},
    };

    static const QMap<Tables, QMutex *> tableToMutex {
        {Tables::Users, &users_},
        {Tables::Chats, &chats_},
        {Tables::ChatUsers, &chatUsers_},
        {Tables::Messages, &messages_},
    };

    QMutexLocker lock{tableToMutex[table]};

    const QString query = QString{"SELECT MAX(DATETIME(updated_at)) AS last_updated_at FROM %1;"}
                              .arg(tableToString[table]);

    SqlQuery getLastUpdatedAtQuery{query};

    if (!executeQuery(getLastUpdatedAtQuery, ErrorImportance::Critical)) {
        return QDateTime{};
    }

    getLastUpdatedAtQuery.first();
    return getLastUpdatedAtQuery.value(0).toDateTime();
}

bool DatabaseClient::addOrUpdateUser(const User &user)
{
    QMutexLocker lock{&users_};
    bool success = UsersTable::addOrUpdateUser(user);

    if (success)
        emit userAdded(user);

    return success;
}

User DatabaseClient::getUserById(int userId)
{
    QMutexLocker lock{&users_};
    return UsersTable::getUserById(userId);
}

bool DatabaseClient::addOrUpdateChat(const Chat &chat)
{
    QMutexLocker lock{&chats_};
    const bool success = ChatsTable::addOrUpdateChat(chat);

    if (success)
        emit chatAdded(chat);

    return success;
}

bool DatabaseClient::addChat(Chat chat, const QList<ChatUser> &chatUsers, int ownUserId)
{
    QMutexLocker lockChats{&chats_};
    QMutexLocker lockChatUsers{&chatUsers_};

    bool success = executeTransaction(*threadDb(), [&]() {
        if (chat.type() == Chat::Type::Private) {
            auto it = std::find_if(chatUsers.begin(), chatUsers.end(), [&](const ChatUser &chatUser) {
                return chatUser.userId() != ownUserId;
            });
            chat.setName(UsersTable::getUserById(it->userId()).username());
        }
        
        if (!ChatsTable::addOrUpdateChat(chat))
            return false;

        for (const auto &chatUser : chatUsers) {
            if (!ChatUsersTable::addOrUpdateChatUser(chatUser))
                return false;
        }

        return true;
    });

    if (success)
        emit chatAdded(chat);

    return success;
}

QList<Chat> DatabaseClient::getAllChats()
{
    QMutexLocker lock{&chats_};
    return ChatsTable::getAllChats();
}

SqlQuery DatabaseClient::getChatsView()
{
    QMutexLocker lock{&chatsView_};
    SqlQuery query{"SELECT * FROM chats_view;"};
    query.exec();
    return query;
}

bool DatabaseClient::addOrUpdateMessage(const Message &message)
{
    QMutexLocker lock{&messages_};
    bool success = MessagesTable::addOrUpdateMessage(message);

    if (success)
        emit messageAdded(message);

    return success;
}

QList<Message> DatabaseClient::getMessages(int chatId)
{
    QMutexLocker lock{&messages_};
    return MessagesTable::getMessagesFromChat(chatId);
}

bool DatabaseClient::addOrUpdateChatUser(const ChatUser &chatUser)
{
    QMutexLocker lock{&chatUsers_};
    return ChatUsersTable::addOrUpdateChatUser(chatUser);
}

DatabaseClient::DatabaseClient()
{
}
