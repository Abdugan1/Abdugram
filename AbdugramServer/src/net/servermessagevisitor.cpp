#include "servermessagevisitor.h"
#include "net_common/messages/syncchatsrequest.h"
#include "server.h"

#include <net_common/tcpsession.h>

#include <net_common/messages/registermessage.h>
#include <net_common/messages/registerstatusmessage.h>
#include <net_common/messages/loginmessage.h>
#include <net_common/messages/loginstatusmessage.h>
#include <net_common/messages/searchonservermessage.h>
#include <net_common/messages/searchusersresultmessage.h>
#include <net_common/messages/createprivatechatmessage.h>
#include <net_common/messages/createprivatechatresultmessage.h>

#include <sql_server/userstable.h>
#include <sql_server/chatstable.h>

#include <sql_common/data_structures/user.h>

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

    if (loginStatus->success())
        loginStatus->setUserId(UsersTable::getUserId(username));

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

void ServerMessageVisitor::visit(const SearchOnServerMessage &message)
{
    const QString searchText = message.searchText();

    AnyMessagePtr<SearchUsersResultMessage> searchResult{new SearchUsersResultMessage};
    searchResult->setUsers(UsersTable::getUsersByLikeSearch("%" + searchText + "%"));

    server_->sendToClient(client_, static_cast<AbduMessagePtr>(searchResult));
}

void ServerMessageVisitor::visit(const SearchUsersResultMessage &message)
{
    Q_UNUSED(message);
}

void ServerMessageVisitor::visit(const CreatePrivateChatMessage &message)
{
    const int user1Id = message.user1Id();
    const int user2Id = message.user2Id();

    using ResultMessage = AnyMessagePtr<CreatePrivateChatResultMessage>;
    ResultMessage createPrivateChatResultMessage{new CreatePrivateChatResultMessage};
    createPrivateChatResultMessage->setChatId(ChatsTable::createPrivateChat(user1Id, user2Id));

    createPrivateChatResultMessage->setSecondParticipiant(UsersTable::getUserById(user2Id));
    server_->sendToClient(client_, static_cast<AbduMessagePtr>(createPrivateChatResultMessage));

    createPrivateChatResultMessage->setSecondParticipiant(UsersTable::getUserById(user1Id));
    server_->sendToClient(user1Id, static_cast<AbduMessagePtr>(createPrivateChatResultMessage));
}

void ServerMessageVisitor::visit(const CreatePrivateChatResultMessage &message)
{

}
