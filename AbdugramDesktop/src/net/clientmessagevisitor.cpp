#include "net/clientmessagevisitor.h"
#include "net/networkhandler.h"

#include <net_common/messages/loginstatusmessage.h>
#include <net_common/messages/registerstatusmessage.h>
#include <net_common/messages/syncusersreply.h>
#include <net_common/messages/syncchatsreply.h>
#include <net_common/messages/syncmessagesreply.h>
#include <net_common/messages/searchusersresultmessage.h>
#include <net_common/messages/createchatresultmessage.h>
#include <net_common/messages/sendmessageresultmessage.h>


#include <sql_common/data_structures/user.h>
#include <sql_common/data_structures/chatuser.h>
#include <sql_common/data_structures/message.h>
#include <sql_common/functions.h>

#include <sql_client/databaseclient.h>

#include <QDebug>

void ClientMessageVisitor::visit(const LoginStatusMessage &message)
{
    qDebug() << "success login?" << message.success();

    if (!message.success()) {
        return;
    }

    networkHandler()->userId_ = message.userId();

    database()->connectToDatabase(networkHandler()->userId_);

    const auto lastUpdatedAt = database()->getLastUpdatedAt(DatabaseClient::Tables::Users);
    networkHandler()->sendSyncUsersRequest(lastUpdatedAt);

    networkHandler()->emitLoginSuccessfully();
}

void ClientMessageVisitor::visit(const RegisterStatusMessage &message)
{
    qDebug() << "success registration?" << message.success();
    if (message.success()) {
        networkHandler()->emitRegisterSuccessfully();
    }
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
    qDebug() << "unsync chats";
    const QHash<Chat, QList<ChatUser> > unsyncChats = reply.unsyncChats();
    for (auto it = unsyncChats.begin(); it != unsyncChats.end(); ++it) {
        const Chat &chat = it.key();
        const QList<ChatUser> chatUsers = it.value();
        qDebug() << "chat id:" << chat.id();
        for (const auto &chatUser : chatUsers) {
            qDebug() << "chat user chat id:" << chatUser.chatId() << "user id:" << chatUser.userId();
        }

        database()->addChat(chat, chatUsers, networkHandler()->userId());
    }

    const auto lastUpdatedAt = database()->getLastUpdatedAt(DatabaseClient::Tables::Messages);
    networkHandler()->sendSyncMessagesRequest(lastUpdatedAt);
}

void ClientMessageVisitor::visit(const SyncMessagesReply &reply)
{
    qDebug() << "unsync messages";
    const QList<Message> unsyncMessages = reply.unsyncMessages();
    for (const auto &message : unsyncMessages) {
        qDebug() << message.text();
        database()->addOrUpdateMessage(message);
    }

    emit networkHandler()->syncFinished();
}

void ClientMessageVisitor::visit(const SearchUsersResultMessage &message)
{
    const QList<User> users = message.users();

    bool success = executeTransaction([&]() {
        for (const auto& user : users) {
            if (!database()->addOrUpdateUser(user)) {
                return false;
            }
        }
        return true;
    });

    if (success)
        networkHandler()->emitSearchResult(users);
}


void ClientMessageVisitor::visit(const CreateChatResultMessage &message)
{
    Chat                  chat      = message.chat();
    const QList<ChatUser> chatUsers = message.chatUsers();

    database()->addChat(chat, chatUsers, networkHandler()->userId());
}

void ClientMessageVisitor::visit(const SendMessageResultMessage &message)
{
    const Message msg = message.message();

    database()->addOrUpdateMessage(msg);
}
