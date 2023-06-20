#include "servermessagevisitor.h"
#include "networkhandler.h"

#include <net_common/tcpsession.h>

#include <net_common/messages/loginmessage.h>
#include <net_common/messages/registermessage.h>
#include <net_common/messages/syncusersmessage.h>
#include <net_common/messages/syncchatsrequest.h>
#include <net_common/messages/syncmessagesrequest.h>
#include <net_common/messages/searchonservermessage.h>
#include <net_common/messages/createchatmessage.h>
#include <net_common/messages/sendmessagemessage.h>

#include <sql_common/data_structures/user.h>
#include <sql_common/data_structures/chatuser.h>
#include <sql_common/functions.h>

#include <sql_server/databaseserver.h>

#include <QSqlDatabase>
#include <QHash>
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

    const QList<User> unsyncUsers = database()->getUnsyncUsers(userId, lastUpdatedAt);

    emit networkHandler_->requestSyncUsersReply(client_, unsyncUsers);
}

void ServerMessageVisitor::visit(const LoginMessage &message)
{
    const QString username = message.username();
    const QString password = message.password();

    const bool isUserExists = database()->isUserExists(username, password);
    int   userId = -1;

    if (isUserExists) {
        userId = database()->getUserIdByUsername(username);
        networkHandler_->addSession(userId, client_);
    }

    emit networkHandler_->requestLoginReply(client_, isUserExists, userId);
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
