#include "clientmessagevisitor.h"
#include "networkhandler.h"

#include <net_common/messages/loginstatusmessage.h>
#include <net_common/messages/registerstatusmessage.h>
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
    if (message.success()) {
        networkHandler()->userId_ = message.user().id();
        database()->addOrIgnoreUser(message.user());
        networkHandler()->emitLoginSuccessfully();
    }
}

void ClientMessageVisitor::visit(const RegisterStatusMessage &message)
{
    qDebug() << "success registration?" << message.success();
    if (message.success()) {
        networkHandler()->emitRegisterSuccessfully();
    }
}

void ClientMessageVisitor::visit(const SearchUsersResultMessage &message)
{
    const QList<User> users = message.users();

    bool success = executeTransaction([&]() {
        for (const auto& user : users) {
            if (!database()->addOrIgnoreUser(user)) {
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

    database()->addMessage(msg);
}
