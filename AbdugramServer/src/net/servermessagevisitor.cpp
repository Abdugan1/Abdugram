#include "servermessagevisitor.h"
#include "net_common/messages/syncchatsrequest.h"
#include "server.h"

#include <net_common/tcpsession.h>

#include <net_common/messages/loginmessage.h>
#include <net_common/messages/registermessage.h>
#include <net_common/messages/searchonservermessage.h>
#include <net_common/messages/createchatmessage.h>
#include <net_common/messages/sendmessagemessage.h>

#include <net_common/messages/loginstatusmessage.h>
#include <net_common/messages/registerstatusmessage.h>
#include <net_common/messages/searchusersresultmessage.h>
#include <net_common/messages/createchatresultmessage.h>
#include <net_common/messages/sendmessageresultmessage.h>

#include <sql_server/userstable.h>
#include <sql_server/chatstable.h>
#include <sql_server/chatuserstable.h>
#include <sql_server/messagestable.h>

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
        int userId = UsersTable::getUserIdByUsername(username);
        loginStatus->setUser(UsersTable::getUserById(userId));
        server_->addSession(loginStatus->user().id(), client_);
    }

    server_->sendToClient(client_, static_cast<AbduMessagePtr>(loginStatus));
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

void ServerMessageVisitor::visit(const CreateChatMessage &message)
{
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


    if (!success)
        return;


    // Result
    const Chat            addedChat      = ChatsTable::getChatById(addedChatId);
    const QList<ChatUser> addedChatUsers = ChatUsersTable::getChatUsers(addedChatId);

    using ResultMessage = AnyMessagePtr<CreateChatResultMessage>;
    ResultMessage createChatResultMessage{new CreateChatResultMessage};
    createChatResultMessage->setChat(addedChat);
    createChatResultMessage->setChatUsers(addedChatUsers);

    for (const auto &chatUser : addedChatUsers) {
        server_->sendToClient(chatUser.userId(), static_cast<AbduMessagePtr>(createChatResultMessage));
    }
}

void ServerMessageVisitor::visit(const SendMessageMessage &message)
{
    const Message msg = message.message();
    const int addedMessageId = MessagesTable::addMessage(msg);

    qDebug() << "addedMessageId:" << addedMessageId;

    if (addedMessageId == -1)
        return;

    qDebug() << "Crossed";

    const Message addedMessage = MessagesTable::getMessageById(addedMessageId);
    AnyMessagePtr<SendMessageResultMessage> resultMessage{new SendMessageResultMessage};
    resultMessage->setMessage(addedMessage);

    const QList<ChatUser> chatUsers = ChatUsersTable::getChatUsers(msg.chatId());
    qDebug() << "chatUsers.size:" << chatUsers.size();

    for (const auto &chatUser : chatUsers) {
        server_->sendToClient(chatUser.userId(), static_cast<AbduMessagePtr>(resultMessage));
        qDebug() << chatUser.userId();
    }
}
