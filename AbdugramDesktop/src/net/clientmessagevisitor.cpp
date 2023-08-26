#include "net/clientmessagevisitor.h"
#include "net/networkhandler.h"

#include <net_common/messages/loginreply.h>
#include <net_common/messages/registerreply.h>

#include <net_common/messages/syncusersreply.h>
#include <net_common/messages/syncchatsreply.h>
#include <net_common/messages/syncmessagesreply.h>
#include <net_common/messages/syncmessagereadsreply.h>

#include <net_common/messages/searchusersreply.h>
#include <net_common/messages/createchatreply.h>
#include <net_common/messages/sendmessagereply.h>
#include <net_common/messages/messagereadreply.h>
#include <net_common/messages/messagesupdated.h>

#include <sql_common/data_structures/user.h>
#include <sql_common/data_structures/chatuser.h>
#include <sql_common/data_structures/message.h>
#include <sql_common/data_structures/messagereads.h>
#include <sql_common/functions.h>

#include <sql_client/databaseclient.h>
#include <sql_client/database.h>

#include <QThread>
#include <QDebug>

void ClientMessageVisitor::visit(const LoginReply &reply)
{
    if (!reply.success()) {
        emit networkHandler()->loginResult(false);
        return;
    }

    networkHandler()->userId_ = reply.userId();

    database()->setOwnId(reply.userId());

    networkHandler()->startSync();

    emit networkHandler()->loginResult(true);
}

void ClientMessageVisitor::visit(const RegisterReply &reply)
{
    if (!reply.success()) {
        emit networkHandler()->registerResult(false);
        return;
    }

    const auto user = reply.user();

    networkHandler()->userId_ = user.id();

    database()->setOwnId(user.id());

    database()->addOrUpdateUser(user);

    emit networkHandler()->registerResult(true);

    // Since we are new user, nothing to sync rather than own user data...
    emit networkHandler()->syncFinished();
}

void ClientMessageVisitor::visit(const SyncUsersReply &reply)
{
    const QList<User> unsyncUsers = reply.users();
    qDebug() << "sync users count:" << unsyncUsers.count();
    for (const auto& user : unsyncUsers) {
        database()->addOrUpdateUser(user);
    }

    emit networkHandler()->usersSyncFinished();
}

void ClientMessageVisitor::visit(const SyncChatsReply &reply)
{
    const QHash<Chat, QList<ChatUser> > unsyncChats = reply.unsyncChats();
    qDebug() << "sync chats count:" << unsyncChats.count();
    for (auto it = unsyncChats.begin(); it != unsyncChats.end(); ++it) {
        const Chat &chat = it.key();
        const QList<ChatUser> chatUsers = it.value();
        qDebug() << "sync chats users count:" << chatUsers.count();
        database()->addChat(chat, chatUsers, networkHandler()->userId());
    }

    emit networkHandler()->chatsAndChatUsersSyncFinished();
}

void ClientMessageVisitor::visit(const SyncMessagesReply &reply)
{
    const QList<Message> unsyncMessages = reply.unsyncMessages();
    qDebug() << "sync messages count:" << unsyncMessages.count();
    for (const auto &message : unsyncMessages) {
        database()->addOrUpdateMessage(message);
    }

    emit networkHandler()->messagesSyncFinished();
}

void ClientMessageVisitor::visit(const SyncMessageReadsReply &reply)
{
    const QList<MessageRead> unsyncMessageReads = reply.unsyncMessageReads();
    qDebug() << "sync message reads count:" << unsyncMessageReads.count();
    database()->addOrUpdateMessageReads(unsyncMessageReads);

    emit networkHandler()->messageReadsSyncFinished();
}

void ClientMessageVisitor::visit(const SearchUsersReply &reply)
{
    const QList<User> users = reply.users();

    bool success = executeTransaction(*database()->threadDb(), [&]() {
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
    networkHandler()->userId_ = -1;
    database()->setOwnId(-1);

    emit networkHandler()->loggedOut();
}

void ClientMessageVisitor::visit(const MessageReadReply &reply)
{
    const QList<MessageRead> messageReads = reply.messageReads();

    database()->addOrUpdateMessageReads(messageReads);
}

void ClientMessageVisitor::visit(const MessagesUpdated &reply)
{
    const QList<Message> messages = reply.messages();

    database()->updateMessages(messages);
}
