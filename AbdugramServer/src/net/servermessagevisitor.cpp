#include "servermessagevisitor.h"
#include "net_common/messages/syncchatsrequest.h"
#include "server.h"

#include <net_common/tcpsession.h>

#include <net_common/messages/registermessage.h>
#include <net_common/messages/registerstatusmessage.h>
#include <net_common/messages/loginmessage.h>
#include <net_common/messages/loginstatusmessage.h>


#include <sql_server/userstable.h>

#include <data_structures/user.h>

#include <QDebug>

ServerMessageVisitor::ServerMessageVisitor(Server *server, TcpSession *client)
    : server_{server}
    , client_{client}
{

}

void ServerMessageVisitor::visit(const RegisterMessage &message)
{
    AnyMessagePtr<RegisterStatusMessage> registerStatus{new RegisterStatusMessage};
    if (UsersTable::isUsernameExists(message.username())) {
        registerStatus->setSuccess(false);
    } else {
        registerStatus->setSuccess(true);

        User user;
        user.setUsername(message.username());
        user.setFirstName(message.firstName());
        user.setLastName(message.lastName());
        user.setEmail(message.email());
        user.setPhone(message.phone());

        UsersTable::addUser(user, message.password());
    }

    server_->sendToClient(client_, static_cast<AbduMessagePtr>(registerStatus));
}

void ServerMessageVisitor::visit(const LoginMessage &message)
{
    const QString username = message.username();
    const QString password = message.password();

    AnyMessagePtr<LoginStatusMessage> loginStatus{new LoginStatusMessage};
    loginStatus->setSuccess(UsersTable::isUserExists(username, password));

    server_->sendToClient(client_, static_cast<AbduMessagePtr>(loginStatus));
}

void ServerMessageVisitor::visit(const RegisterStatusMessage &message)
{
    Q_UNUSED(message);
}

void ServerMessageVisitor::visit(const LoginStatusMessage &message)
{
    Q_UNUSED(message);
}

void ServerMessageVisitor::visit(const SyncChatsRequest &message)
{
    const QString   username   = message.fromUsername();
    const QDateTime lastUpdate = message.lastUpdate();

}
