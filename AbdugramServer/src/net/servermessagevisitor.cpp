#include "net/servermessagevisitor.h"
#include "net/networkhandler.h"
#include "net/session.h"

#include <net_common/messages/loginrequest.h>
#include <net_common/messages/registerrequest.h>
#include <net_common/messages/syncusersrequest.h>
#include <net_common/messages/syncchatsrequest.h>
#include <net_common/messages/syncmessagesrequest.h>
#include <net_common/messages/searchrequest.h>
#include <net_common/messages/createchatrequest.h>
#include <net_common/messages/sendmessagerequest.h>
#include <net_common/messages/logoutrequest.h>

#include <sql_common/data_structures/user.h>
#include <sql_common/data_structures/chatuser.h>
#include <sql_common/functions.h>

#include <sql_server/databaseserver.h>

#include <QSqlDatabase>
#include <QHash>
#include <QDebug>

ServerMessageVisitor::ServerMessageVisitor(NetworkHandler *networkHandler, Session *client)
    : networkHandler_{networkHandler}
    , client_{client}
{

}

void ServerMessageVisitor::visit(const LoginRequest &request)
{
    const QString username = request.username();
    const QString password = request.password();

    const bool isUserExists = database()->isUserExists(username, password);
    User user;

    if (isUserExists) {
        user = database()->getUserById(database()->getUserIdByUsername(username));
        networkHandler_->addSession(user.id(), client_);
    }

    emit networkHandler_->requestLoginReply(client_, isUserExists, user);
}


void ServerMessageVisitor::visit(const RegisterRequest &request)
{
    const bool isUsernameExists = database()->isUsernameExists(request.username());
    User user;

    if (!isUsernameExists) {
        user.setUsername(request.username());
        user.setFirstName(request.firstName());
        user.setEmail(request.email());
        user.setPhone(request.phone());

        database()->addUser(user, request.password());
    }

    const int addedUserId = database()->lastInsertedId(DatabaseServer::Tables::Users);

    networkHandler_->addSession(addedUserId, client_);

    user = database()->getUserById(addedUserId);

    emit networkHandler_->requestRegisterReply(client_, !isUsernameExists, user);
}

void ServerMessageVisitor::visit(const SyncUsersRequest &request)
{
    const int       userId        = request.userId();
    const QDateTime lastUpdatedAt = request.lastUpdatedAt();

    const QList<User> unsyncUsers = database()->getUnsyncUsers(userId, lastUpdatedAt);

    emit networkHandler_->requestSyncUsersReply(client_, unsyncUsers);
}

void ServerMessageVisitor::visit(const SyncChatsRequest &request)
{
    const int       userId                 = request.userId();
    const QDateTime chatsLastUpdatedAt     = request.chatsLastUpdatedAt();
    const QDateTime chatUsersLastUpdatedAt = request.chatUsersLastUpdatedAt();

    const QList<Chat> chats = database()->getUnsyncChats(userId, chatsLastUpdatedAt);

    QHash<Chat, QList<ChatUser>> unsyncChats;
    for (const auto &chat : chats) {
        unsyncChats.insert(chat, database()->getUnsyncChatUsers(userId, chat.id(), chatsLastUpdatedAt));
    }

    emit networkHandler_->requestSyncChatsReply(client_, unsyncChats);
}

void ServerMessageVisitor::visit(const SyncMessagesRequest &request)
{
    const int       userId        = request.userId();
    const QDateTime lastUpdatedAt = request.lastUpdatedAt();

    const QList<Message> unsyncMessages = database()->getUnsyncMessages(userId, lastUpdatedAt);

    emit networkHandler_->requestSyncMessagesReply(client_, unsyncMessages);
}

void ServerMessageVisitor::visit(const SearchRequest &request)
{
    const QString searchText = request.searchText();

    const QList<User> foundUsers = database()->getUsersByLikeSearch("%" + searchText + "%");

    emit networkHandler_->requestSearchReply(client_, foundUsers);
}

void ServerMessageVisitor::visit(const CreateChatRequest &message)
{
    const Chat            chat      = message.chat();
    const QList<ChatUser> chatUsers = message.chatUsers();

    const bool success = database()->addChat(chat, chatUsers);

    if (!success)
        return;

    const int addedChatId = database()->lastInsertedId(DatabaseServer::Tables::Chats);

    const Chat            addedChat      = database()->getChatById(addedChatId);
    const QList<ChatUser> addedChatUsers = database()->getChatUsers(addedChatId);

    QList<User> users;
    for (const auto &chatUser : addedChatUsers) {
        users.append(database()->getUserById(chatUser.userId()));
    }

    for (const auto &chatUser : addedChatUsers) {
        emit networkHandler_->requestCreateChatReply(chatUser.userId(), addedChat, users, addedChatUsers);
    }
}

void ServerMessageVisitor::visit(const SendMessageRequest &request)
{
    const Message message = request.message();

    if (!database()->addMessage(message))
        return;

    const int addedMessageId = database()->lastInsertedId(DatabaseServer::Tables::Messages);
    const Message addedMessage = database()->getMessageById(addedMessageId);

    const QList<ChatUser> chatUsers = database()->getChatUsers(message.chatId());

    for (const auto &chatUser : chatUsers) {
        emit networkHandler_->requestSendMessageReply(chatUser.userId(), addedMessage);
    }
}

void ServerMessageVisitor::visit(const LogoutRequest &request)
{
    networkHandler_->removeSession(client_->userId());

    emit networkHandler_->requestLogoutReply(client_);
}
