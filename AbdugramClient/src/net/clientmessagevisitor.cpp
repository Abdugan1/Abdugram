#include "clientmessagevisitor.h"
#include "networkhandler.h"

#include <net_common/messages/registerstatusmessage.h>
#include <net_common/messages/loginstatusmessage.h>
#include <net_common/messages/searchusersresultmessage.h>
#include <net_common/messages/createchatresultmessage.h>

#include <sql_common/data_structures/user.h>

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
    for (const auto& user : users) {
        qDebug() << "username:" << user.username();
        qDebug() << "updatedAt" << user.updatedAt();
    }
    networkHandler()->emitSearchResult(users);
}

void ClientMessageVisitor::visit(const CreateChatMessage &message)
{
}

void ClientMessageVisitor::visit(const CreateChatResultMessage &message)
{
//    const Chat            chat      = message.chat();
//    const QList<ChatUser> chatUsers = message.chatUsers();
}
