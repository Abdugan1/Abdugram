#include "clientmessagevisitor.h"
#include "networkhandler.h"

#include <net_common/messages/registerstatusmessage.h>
#include <net_common/messages/loginstatusmessage.h>
#include <net_common/messages/searchusersresultmessage.h>
#include <net_common/messages/createchatresultmessage.h>

#include <sql_common/data_structures/user.h>
#include <sql_common/data_structures/chatuser.h>
#include <sql_common/functions.h>

#include <sql_client/userstable.h>
#include <sql_client/chatstable.h>
#include <sql_client/chatuserstable.h>

#include <QDebug>

ClientMessageVisitor::ClientMessageVisitor()
{
}

void ClientMessageVisitor::visit(const RegisterMessage &message)
{
    Q_UNUSED(message);
}

void ClientMessageVisitor::visit(const LoginMessage &message)
{
    Q_UNUSED(message);
}

void ClientMessageVisitor::visit(const RegisterStatusMessage &message)
{
    qDebug() << "success registration?" << message.success();
    if (message.success()) {
        networkHandler()->emitRegisterSuccessfully();
    }
}

void ClientMessageVisitor::visit(const LoginStatusMessage &message)
{
    qDebug() << "Success login?" << message.success();
    if (message.success()) {
        networkHandler()->emitLoginSuccessfully();
        networkHandler()->userId_ = message.userId();
    }
}

void ClientMessageVisitor::visit(const SyncChatsRequest &message)
{

}

void ClientMessageVisitor::visit(const SearchOnServerMessage &message)
{
    Q_UNUSED(message);
}

void ClientMessageVisitor::visit(const SearchUsersResultMessage &message)
{
    const QList<User> users = message.users();

    bool success = executeTransaction([&]() {
        for (const auto& user : users) {
            if (!UsersTable::addOrIgnoreUser(user)) {
                return false;
            }
        }
        return true;
    });

    if (success)
        networkHandler()->emitSearchResult(users);
}

void ClientMessageVisitor::visit(const CreateChatMessage &message)
{
}

void ClientMessageVisitor::visit(const CreateChatResultMessage &message)
{
    Chat                  chat      = message.chat();
    const QList<ChatUser> chatUsers = message.chatUsers();

    bool success = executeTransaction([&]() {
        if (chat.type() == Chat::Type::Private) {
            auto it = std::find_if(chatUsers.begin(), chatUsers.end(), [&](const ChatUser &chatUser) {
                return chatUser.userId() != networkHandler()->userId();
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

    if (success) {
        networkHandler()->emitNewChatAdded(chat.id());
    }
}
