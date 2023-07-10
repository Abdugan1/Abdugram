#include "net/clientmessagevisitor.h"
#include "net/networkhandler.h"

#include <net_common/messages/loginreply.h>
#include <net_common/messages/registerreply.h>
#include <net_common/messages/syncusersreply.h>
#include <net_common/messages/syncchatsreply.h>
#include <net_common/messages/syncmessagesreply.h>
#include <net_common/messages/searchusersreply.h>
#include <net_common/messages/createchatreply.h>
#include <net_common/messages/sendmessagereply.h>


#include <sql_common/data_structures/user.h>
#include <sql_common/data_structures/chatuser.h>
#include <sql_common/data_structures/message.h>
#include <sql_common/functions.h>

#include <sql_client/databaseclient.h>

#include <QDebug>

void ClientMessageVisitor::visit(const LoginReply &reply)
{
    if (!reply.success()) {
        emit networkHandler()->loginResult(false);
        return;
    }

    User user = reply.user();
    user.setCreatedAt(QDateTime{});
    user.setUpdatedAt(QDateTime{});
    user.setDeletedAt(QDateTime{});

    networkHandler()->userId_ = user.id();

    database()->connectToDatabase(user.id());
    database()->addOrUpdateUser(user);

    const auto lastUpdatedAt = database()->getLastUpdatedAt(DatabaseClient::Tables::Users);
    networkHandler()->sendSyncUsersRequest(lastUpdatedAt);

    emit networkHandler()->loginResult(true);
}

void ClientMessageVisitor::visit(const RegisterReply &reply)
{
    if (!reply.success()) {
        emit networkHandler()->registerResult(false);
        return;
    }

    const User user = reply.user();

    networkHandler()->userId_ = user.id();

    database()->connectToDatabase(user.id());
    database()->addOrUpdateUser(user);

    emit networkHandler()->registerResult(true);
}

void ClientMessageVisitor::visit(const SyncUsersReply &reply)
{
    const QList<User> unsyncUsers = reply.users();
    for (const auto& user : unsyncUsers) {
        database()->addOrUpdateUser(user);
    }

    const auto chatsLastUpdatedAt     = database()->getLastUpdatedAt(DatabaseClient::Tables::Chats);
    const auto chatUsersLastUpdatedAt = database()->getLastUpdatedAt(DatabaseClient::Tables::ChatUsers);
    networkHandler()->sendSyncChatsRequest(chatsLastUpdatedAt, chatUsersLastUpdatedAt);
}

void ClientMessageVisitor::visit(const SyncChatsReply &reply)
{
    const QHash<Chat, QList<ChatUser> > unsyncChats = reply.unsyncChats();
    for (auto it = unsyncChats.begin(); it != unsyncChats.end(); ++it) {
        const Chat &chat = it.key();
        const QList<ChatUser> chatUsers = it.value();
        database()->addChat(chat, chatUsers, networkHandler()->userId());
    }

    const auto lastUpdatedAt = database()->getLastUpdatedAt(DatabaseClient::Tables::Messages);
    networkHandler()->sendSyncMessagesRequest(lastUpdatedAt);
}

void ClientMessageVisitor::visit(const SyncMessagesReply &reply)
{
    const QList<Message> unsyncMessages = reply.unsyncMessages();
    for (const auto &message : unsyncMessages) {
        database()->addOrUpdateMessage(message);
    }

    emit networkHandler()->syncFinished();
}

void ClientMessageVisitor::visit(const SearchUsersReply &reply)
{
    const QList<User> users = reply.users();

    bool success = executeTransaction([&]() {
        for (const auto& user : users) {
            if (!database()->addOrUpdateUser(user)) {
                return false;
            }
        }
        return true;
    });

    if (success)
        emit networkHandler()->searchResult(users);
}


void ClientMessageVisitor::visit(const CreateChatReply &reply)
{
    const Chat            chat      = reply.chat();
    const QList<User>     users     = reply.users();
    const QList<ChatUser> chatUsers = reply.chatUsers();

    for (const auto& user : users) {
        database()->addOrUpdateUser(user);
    }
    database()->addChat(chat, chatUsers, networkHandler()->userId());
}

void ClientMessageVisitor::visit(const SendMessageReply &reply)
{
    const Message msg = reply.message();

    database()->addOrUpdateMessage(msg);
}

void ClientMessageVisitor::visit(const LogoutReply &reply)
{
    qDebug() << "logout...";
    networkHandler()->userId_ = -1;

    emit networkHandler()->loggedOut();
}
