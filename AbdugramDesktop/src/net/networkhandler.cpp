#include "net/networkhandler.h"
#include "net/clientmessagevisitor.h"

#include <net_common/messages/abdumessage.h>
#include <net_common/messages/loginrequest.h>
#include <net_common/messages/registerrequest.h>
#include <net_common/messages/syncusersrequest.h>
#include <net_common/messages/syncchatsrequest.h>
#include <net_common/messages/syncmessagesrequest.h>
#include <net_common/messages/searchrequest.h>
#include <net_common/messages/createchatrequest.h>
#include <net_common/messages/sendmessagerequest.h>
#include <net_common/messages/logoutrequest.h>

#include <net_common/consts.h>

#include <sql_client/databaseclient.h>
#include <sql_common/data_structures/chatuser.h>

NetworkHandler::NetworkHandler(QObject *parent)
    : QObject{parent}
    , tcpSession_{new TcpSession}
{
    connect(tcpSession_, &TcpSession::connected, this, &NetworkHandler::connectedSucessfully);

    connect(tcpSession_, &TcpSession::errorOccurred, this, &NetworkHandler::connectionError);

    connect(tcpSession_, &TcpSession::received, this, &NetworkHandler::onMessageReceived);


    // sync connections
    connect(this, &NetworkHandler::usersSyncFinished,
            this, &NetworkHandler::sendSyncChatsRequest);

    connect(this, &NetworkHandler::chatsAndChatUsersSyncFinished,
            this, &NetworkHandler::sendSyncMessagesRequest);
}

QAbstractSocket::SocketState NetworkHandler::tcpState() const
{
    return tcpSession_->state();
}

bool NetworkHandler::isConnected() const
{
    return tcpSession_->state() == QAbstractSocket::ConnectedState;
}

NetworkHandler *NetworkHandler::instance()
{
    static NetworkHandler self;
    return &self;
}

void NetworkHandler::connectToServer()
{
    if (tcpSession_->state() == QAbstractSocket::ConnectingState)
        tcpSession_->abort();
    tcpSession_->connectToHost(consts::server::Address, consts::server::Port);
}

void NetworkHandler::disconnectFromServer()
{
    tcpSession_->disconnectFromHost();
}

void NetworkHandler::sendToServer(const AbduMessagePtr &message)
{
    if (!isConnected())
        return;
    tcpSession_->send(message);
}

void NetworkHandler::onMessageReceived(const AbduMessagePtr &message)
{
    ClientMessageVisitor visitor;
    message->accept(&visitor);
}

int NetworkHandler::userId() const
{
    return userId_;
}

QString NetworkHandler::lastUsername() const
{
    return lastUsername_;
}

QString NetworkHandler::lastPassword() const
{
    return lastPassword_;
}

void NetworkHandler::sendLoginRequest(const QString &username, const QString &password)
{
    lastUsername_ = username;
    lastPassword_ = password;

    AnyMessagePtr<LoginRequest> loginMessage{new LoginRequest};
    loginMessage->setUsername(username);
    loginMessage->setPassword(password);

    sendToServer(static_cast<AbduMessagePtr>(loginMessage));
}

void NetworkHandler::sendSearchRequest(const QString &searchText)
{
    AnyMessagePtr<SearchRequest> searchOnServerMessage{new SearchRequest{}};
    searchOnServerMessage->setSearchText(searchText);
    sendToServer(static_cast<AbduMessagePtr>(searchOnServerMessage));
}

void NetworkHandler::sendCreateChatRequest(const Chat &chat, const QList<ChatUser> &chatUsers)
{
    AnyMessagePtr<CreateChatRequest> createPrivateChat{new CreateChatRequest};
    createPrivateChat->setChat(chat);
    createPrivateChat->setChatUsers(chatUsers);

    sendToServer(static_cast<AbduMessagePtr>(createPrivateChat));
}

void NetworkHandler::sendSendMessageRequest(const Message &message)
{
    AnyMessagePtr<SendMessageRequest> sendMessage{new SendMessageRequest};
    sendMessage->setMessage(message);

    sendToServer(static_cast<AbduMessagePtr>(sendMessage));
}

void NetworkHandler::startSync()
{
    networkHandler()->sendSyncUsersRequest();
}

void NetworkHandler::sendSyncUsersRequest()
{
    AnyMessagePtr<SyncUsersRequest> syncUsers{new SyncUsersRequest};
    syncUsers->setUserId(userId());

    const auto lastUpdatedAt = database()->getLastUpdatedAt(DatabaseClient::Tables::Users);
    syncUsers->setLastUpdatedAt(lastUpdatedAt.isValid() ? lastUpdatedAt
                                                        : QDateTime{QDate{0, 0, 0}, QTime{0, 0}});

    sendToServer(static_cast<AbduMessagePtr>(syncUsers));
}

void NetworkHandler::sendSyncChatsRequest()
{
    AnyMessagePtr<SyncChatsRequest> syncChats{new SyncChatsRequest};
    syncChats->setUserId(userId());

    const auto chatsLastUpdate     = database()->getLastUpdatedAt(DatabaseClient::Tables::Chats);
    const auto chatUsersLastUpdate = database()->getLastUpdatedAt(DatabaseClient::Tables::ChatUsers);
    syncChats->setChatsLastUpdatedAt(chatsLastUpdate.isValid() ? chatsLastUpdate
                                                               : QDateTime{QDate{0, 0, 0}, QTime{0, 0}});
    syncChats->setChatUsersLastUpdatedAt(chatUsersLastUpdate.isValid() ? chatsLastUpdate
                                                                       : QDateTime{QDate{0, 0, 0}, QTime{0, 0}});

    sendToServer(static_cast<AbduMessagePtr>(syncChats));
}

void NetworkHandler::sendSyncMessagesRequest()
{
    AnyMessagePtr<SyncMessagesRequest> syncMessages{new SyncMessagesRequest};
    syncMessages->setUserId(userId());

    const auto lastUpdate = database()->getLastUpdatedAt(DatabaseClient::Tables::Messages);
    syncMessages->setLastUpdatedAt(lastUpdate.isValid() ? lastUpdate
                                                        : QDateTime{QDate{0, 0, 0}, QTime{0, 0}});

    sendToServer(static_cast<AbduMessagePtr>(syncMessages));
}

void NetworkHandler::sendLogoutRequest()
{
    AnyMessagePtr<LogoutRequest> logoutRequest{new LogoutRequest};

    sendToServer(static_cast<AbduMessagePtr>(logoutRequest));
}

void NetworkHandler::sendRegisterRequest(const QString &firstName,
                                         const QString &username,
                                         const QString &email,
                                         const QString &phone,
                                         const QString &password)
{
    AnyMessagePtr<RegisterRequest> registerMessage{new RegisterRequest};
    registerMessage->setFirstName(firstName);
    registerMessage->setUsername(username);
    registerMessage->setEmail(email);
    registerMessage->setPhone(phone);
    registerMessage->setPassword(password);

    sendToServer(static_cast<AbduMessagePtr>(registerMessage));
}

