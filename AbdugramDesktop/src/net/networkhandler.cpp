#include "net/networkhandler.h"
#include "net/clientmessagevisitor.h"

#include <net_common/messages/abdumessage.h>
#include <net_common/messages/loginrequest.h>
#include <net_common/messages/registerrequest.h>

#include <net_common/messages/syncusersrequest.h>
#include <net_common/messages/syncchatsrequest.h>
#include <net_common/messages/syncmessagesrequest.h>
#include <net_common/messages/syncmessagereadsrequest.h>

#include <net_common/messages/searchrequest.h>
#include <net_common/messages/createchatrequest.h>
#include <net_common/messages/sendmessagerequest.h>
#include <net_common/messages/logoutrequest.h>
#include <net_common/messages/createprivatechatrequest.h>
#include <net_common/messages/messagereadrequest.h>

#include <net_common/consts.h>

#include <sql_client/databaseclient.h>
#include <sql_common/data_structures/chatuser.h>

NetworkHandler::NetworkHandler(QObject *parent)
    : QObject{parent}
    , tcpSession_{new TcpSession{this}}
{
    connect(tcpSession_, &TcpSession::connected, this, &NetworkHandler::connectedSucessfully);

    connect(tcpSession_, &TcpSession::errorOccurred, this, &NetworkHandler::connectionError);

    connect(tcpSession_, &TcpSession::received, this, &NetworkHandler::onMessageReceived);


    // sync connections
    connect(this, &NetworkHandler::usersSyncFinished,
            this, &NetworkHandler::sendSyncChatsRequest);

    connect(this, &NetworkHandler::chatsAndChatUsersSyncFinished,
            this, &NetworkHandler::sendSyncMessagesRequest);

    connect(this, &NetworkHandler::messagesSyncFinished,
            this, &NetworkHandler::sendSyncMessageReadsRequest);

    connect(this, &NetworkHandler::messageReadsSyncFinished,
            this, &NetworkHandler::syncFinished);
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
    emit tcpSession_->requestSend(message);
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

    AnyMessagePtr<LoginRequest> loginRequest{new LoginRequest};
    loginRequest->setUsername(username);
    loginRequest->setPassword(password);

    sendToServer(static_cast<AbduMessagePtr>(loginRequest));
}

void NetworkHandler::sendSearchRequest(const QString &searchText)
{
    AnyMessagePtr<SearchRequest> searchOnServerRequest{new SearchRequest{}};
    searchOnServerRequest->setSearchText(searchText);
    sendToServer(static_cast<AbduMessagePtr>(searchOnServerRequest));
}

void NetworkHandler::sendCreatePrivateChatRequest(const Chat &chat,
                                                  const QList<ChatUser> &chatUsers,
                                                  const Message &message)
{
    AnyMessagePtr<CreatePrivateChatRequest> createPrivateChatRequest{new CreatePrivateChatRequest};
    createPrivateChatRequest->setChat(chat);
    createPrivateChatRequest->setChatUsers(chatUsers);
    createPrivateChatRequest->setMessage(message);

    sendToServer(static_cast<AbduMessagePtr>(createPrivateChatRequest));
}

void NetworkHandler::sendCreateChatRequest(const Chat &chat, const QList<ChatUser> &chatUsers)
{
    AnyMessagePtr<CreateChatRequest> createChatRequest{new CreateChatRequest};
    createChatRequest->setChat(chat);
    createChatRequest->setChatUsers(chatUsers);

    sendToServer(static_cast<AbduMessagePtr>(createChatRequest));
}

void NetworkHandler::sendSendMessageRequest(const Message &message)
{
    AnyMessagePtr<SendMessageRequest> sendMessage{new SendMessageRequest};
    sendMessage->setMessage(message);

    sendToServer(static_cast<AbduMessagePtr>(sendMessage));
}

void NetworkHandler::sendMessageReadRequest(const QList<MessageRead> &messageReads)
{
    AnyMessagePtr<MessageReadRequest> messageReadRequest{new MessageReadRequest};
    messageReadRequest->setMessageReads(messageReads);

    sendToServer(static_cast<AbduMessagePtr>(messageReadRequest));
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

    syncChats->setChatsLastUpdatedAt(chatsLastUpdate);
    syncChats->setChatUsersLastUpdatedAt(chatsLastUpdate);

    sendToServer(static_cast<AbduMessagePtr>(syncChats));
}

void NetworkHandler::sendSyncMessagesRequest()
{
    AnyMessagePtr<SyncMessagesRequest> syncMessages{new SyncMessagesRequest};
    syncMessages->setUserId(userId());

    const auto lastUpdate = database()->getLastUpdatedAt(DatabaseClient::Tables::Messages);
    syncMessages->setLastUpdatedAt(lastUpdate);

    sendToServer(static_cast<AbduMessagePtr>(syncMessages));
}

void NetworkHandler::sendSyncMessageReadsRequest()
{
    AnyMessagePtr<SyncMessageReadsRequest> syncMessageReadsRequest{new SyncMessageReadsRequest};
    syncMessageReadsRequest->setUserId(userId());

    const auto lastUpdate = database()->getLastUpdatedAt(DatabaseClient::Tables::Messages);
    syncMessageReadsRequest->setLastUpdatedAt(lastUpdate);

    sendToServer(static_cast<AbduMessagePtr>(syncMessageReadsRequest));
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
    lastUsername_ = username;
    lastPassword_ = password;

    AnyMessagePtr<RegisterRequest> registerMessage{new RegisterRequest};
    registerMessage->setFirstName(firstName);
    registerMessage->setUsername(username);
    registerMessage->setEmail(email);
    registerMessage->setPhone(phone);
    registerMessage->setPassword(password);

    sendToServer(static_cast<AbduMessagePtr>(registerMessage));
}

