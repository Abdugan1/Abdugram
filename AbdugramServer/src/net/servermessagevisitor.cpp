#include "servermessagevisitor.h"
#include "networkhandler.h"

#include <net_common/tcpsession.h>

#include <net_common/messages/loginmessage.h>
#include <net_common/messages/registermessage.h>
#include <net_common/messages/syncusersmessage.h>
#include <net_common/messages/searchonservermessage.h>
#include <net_common/messages/createchatmessage.h>
#include <net_common/messages/sendmessagemessage.h>

#include <net_common/messages/loginstatusmessage.h>
#include <net_common/messages/registerstatusmessage.h>
#include <net_common/messages/searchusersresultmessage.h>
#include <net_common/messages/createchatresultmessage.h>
#include <net_common/messages/sendmessageresultmessage.h>

#include <sql_common/data_structures/user.h>
#include <sql_common/data_structures/chatuser.h>
#include <sql_common/functions.h>

#include <sql_server/databaseserver.h>

#include <QSqlDatabase>
#include <QDebug>

ServerMessageVisitor::ServerMessageVisitor(NetworkHandler *networkHandler, TcpSession *client)
    : networkHandler_{networkHandler}
    , client_{client}
{

}

void ServerMessageVisitor::visit(const RegisterMessage &message)
{
    const bool isUsernameExists = database()->isUsernameExists(message.username());
    User user;

    if (!isUsernameExists) {
        user.setUsername(message.username());
        user.setFirstName(message.firstName());
        user.setLastName(message.lastName());
        user.setEmail(message.email());
        user.setPhone(message.phone());

        database()->addUser(user, message.password());
    }

    emit networkHandler_->requestRegisterReply(client_, !isUsernameExists, user);
}

void ServerMessageVisitor::visit(const SyncUsersMessage &message)
{
    const int       userId        = message.userId();
    const QDateTime lastUpdatedAt = message.lastUpdatedAt();
    qDebug() << "date time:" << lastUpdatedAt << "is valid?" << lastUpdatedAt.isValid();
    const QList<User> unsyncUsers = database()->getUpdatedUsersForUser(userId, lastUpdatedAt);

    emit networkHandler_->requestSyncUsersReply(client_, unsyncUsers);
}

void ServerMessageVisitor::visit(const LoginMessage &message)
{
    const QString username = message.username();
    const QString password = message.password();
    qDebug() << username;
    qDebug() << password;

    const bool isUserExists = database()->isUserExists(username, password);
    int   userId = -1;

    if (isUserExists) {
        userId = database()->getUserIdByUsername(username);
        networkHandler_->addSession(userId, client_);
    }

    emit networkHandler_->requestLoginReply(client_, isUserExists, userId);
}

void ServerMessageVisitor::visit(const SyncChatsRequest &message)
{

}

void ServerMessageVisitor::visit(const SearchOnServerMessage &message)
{
    const QString searchText = message.searchText();

    const QList<User> foundUsers = database()->getUsersByLikeSearch("%" + searchText + "%");

    emit networkHandler_->requestSearchReply(client_, foundUsers);
}

void ServerMessageVisitor::visit(const CreateChatMessage &message)
{
    const Chat            chat      = message.chat();
    const QList<ChatUser> chatUsers = message.chatUsers();

    const bool success = database()->addChat(chat, chatUsers);

    if (!success)
        return;

    const int addedChatId = database()->lastInsertedId(DatabaseServer::Tables::Chats);

    const Chat            addedChat      = database()->getChatById(addedChatId);
    const QList<ChatUser> addedChatUsers = database()->getChatUsers(addedChatId);

    for (const auto &chatUser : addedChatUsers) {
        emit networkHandler_->requestCreateChatReply(chatUser.userId(), addedChat, addedChatUsers);
    }
}

void ServerMessageVisitor::visit(const SendMessageMessage &message)
{
    const Message msg = message.message();

    if (!database()->addMessage(msg))
        return;

    const int addedMessageId = database()->lastInsertedId(DatabaseServer::Tables::Messages);
    const Message addedMessage = database()->getMessageById(addedMessageId);

    const QList<ChatUser> chatUsers = database()->getChatUsers(msg.chatId());

    for (const auto &chatUser : chatUsers) {
        emit networkHandler_->requestSendMessageReply(chatUser.userId(), addedMessage);
    }
}
