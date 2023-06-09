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
#include <net_common/messages/createchatmessage.h>
#include <net_common/messages/createchatresultmessage.h>

#include <sql_server/userstable.h>
#include <sql_server/chatstable.h>
#include <sql_server/chatuserstable.h>

#include <sql_common/data_structures/user.h>
#include <sql_common/functions.h>

#include <QSqlDatabase>
#include <QDebug>

ServerMessageVisitor::ServerMessageVisitor(Server *server, Session *client)
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

    if (loginStatus->success()) {
        loginStatus->setUserId(UsersTable::getUserIdByUsername(username));
        server_->addSession(loginStatus->userId(), client_);
    }

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

void ServerMessageVisitor::visit(const CreateChatMessage &message)
{
    qDebug() << "Get create new chat message";
    const Chat            chat      = message.chat();
    const QList<ChatUser> chatUsers = message.chatUsers();


    int addedChatId = -1;
    bool success = executeTransaction([&]() {
        addedChatId = ChatsTable::addChat(chat);
        if (addedChatId == -1) {
            return false;
        }

        if (!ChatUsersTable::addUsersToChat(addedChatId, chatUsers)) {
            return false;
        }

        return true;
    });


    if (!success) {
        qDebug() << "Can't succeed :(";
        return;
    }


    // Result
    qDebug() << "Get chat:";
    const Chat            addedChat      = ChatsTable::getChatById(addedChatId);
    qDebug() << "Get chat users:";
    const QList<ChatUser> addedChatUsers = ChatUsersTable::getChatUsers(addedChatId);

    using ResultMessage = AnyMessagePtr<CreateChatResultMessage>;
    ResultMessage createChatResultMessage{new CreateChatResultMessage};
    createChatResultMessage->setChat(addedChat);
    createChatResultMessage->setChatUsers(addedChatUsers);

    for (const auto &chatUser : addedChatUsers) {
        server_->sendToClient(chatUser.userId(), static_cast<AbduMessagePtr>(createChatResultMessage));
    }
}

void ServerMessageVisitor::visit(const CreateChatResultMessage &message)
{
}
