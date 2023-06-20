#include "networkhandler.h"
#include "clientmessagevisitor.h"

#include <net_common/messages/abdumessage.h>
#include <net_common/messages/loginmessage.h>
#include <net_common/messages/registermessage.h>
#include <net_common/messages/syncusersmessage.h>
#include <net_common/messages/syncchatsrequest.h>
#include <net_common/messages/syncmessagesrequest.h>
#include <net_common/messages/searchonservermessage.h>
#include <net_common/messages/createchatmessage.h>
#include <net_common/messages/sendmessagemessage.h>

#include <net_common/consts.h>

#include <sql_common/data_structures/chatuser.h>

NetworkHandler::NetworkHandler(QObject *parent)
    : QObject{parent}
    , tcpSession_{new TcpSession}
{
    connect(tcpSession_, &TcpSession::connected, this, &NetworkHandler::connectedSucessfully);

    connect(tcpSession_, &TcpSession::errorOccurred, this, &NetworkHandler::connectionError);

    connect(tcpSession_, &TcpSession::received, this, &NetworkHandler::onMessageReceived);
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

void NetworkHandler::emitLoginSuccessfully()
{
    emit loginSuccessfully();
}

void NetworkHandler::emitRegisterSuccessfully()
{
    emit registerSuccessfully();
}

void NetworkHandler::emitSearchResult(const QList<User> &usersSearchResult)
{
    emit searchResult(usersSearchResult);
}

int NetworkHandler::userId() const
{
    return userId_;
}

void NetworkHandler::sendLoginRequest(const QString &username, const QString &password)
{
    AnyMessagePtr<LoginMessage> loginMessage{new LoginMessage};
    loginMessage->setUsername(username);
    loginMessage->setPassword(password);

    sendToServer(static_cast<AbduMessagePtr>(loginMessage));
}

void NetworkHandler::sendSearchRequest(const QString &searchText)
{
    AnyMessagePtr<SearchOnServerMessage> searchOnServerMessage{new SearchOnServerMessage{}};
    searchOnServerMessage->setSearchText(searchText);
    sendToServer(static_cast<AbduMessagePtr>(searchOnServerMessage));
}

void NetworkHandler::sendCreateChatRequest(const Chat &chat, const QList<ChatUser> &chatUsers)
{
    AnyMessagePtr<CreateChatMessage> createPrivateChat{new CreateChatMessage};
    createPrivateChat->setChat(chat);
    createPrivateChat->setChatUsers(chatUsers);

    sendToServer(static_cast<AbduMessagePtr>(createPrivateChat));
}

void NetworkHandler::sendSendMessageRequest(const Message &message)
{
    AnyMessagePtr<SendMessageMessage> sendMessage{new SendMessageMessage};
    sendMessage->setMessage(message);

    sendToServer(static_cast<AbduMessagePtr>(sendMessage));
}

void NetworkHandler::sendSyncUsersRequest(const QDateTime &chatsLastUpdatedAt)
{
    AnyMessagePtr<SyncUsersMessage> syncUsers{new SyncUsersMessage};
    syncUsers->setUserId(userId());
    syncUsers->setLastUpdatedAt(chatsLastUpdatedAt.isValid() ? chatsLastUpdatedAt : QDateTime{QDate{0, 0, 0}, QTime{0, 0}});

    sendToServer(static_cast<AbduMessagePtr>(syncUsers));
}

void NetworkHandler::sendSyncChatsRequest(const QDateTime &chatsLastUpdate, const QDateTime &chatUsersLastUpdate)
{
    AnyMessagePtr<SyncChatsRequest> syncChats{new SyncChatsRequest};
    syncChats->setUserId(userId());
    syncChats->setChatsLastUpdatedAt(chatsLastUpdate.isValid() ? chatsLastUpdate : QDateTime{QDate{0, 0, 0}, QTime{0, 0}});
    syncChats->setChatUsersLastUpdatedAt(chatUsersLastUpdate.isValid() ? chatsLastUpdate : QDateTime{QDate{0, 0, 0}, QTime{0, 0}});

    sendToServer(static_cast<AbduMessagePtr>(syncChats));
}

void NetworkHandler::sendSyncMessagesRequest(const QDateTime &lastUpdate)
{
    AnyMessagePtr<SyncMessagesRequest> syncMessages{new SyncMessagesRequest};
    syncMessages->setUserId(userId());
    syncMessages->setLastUpdatedAt(lastUpdate.isValid() ? lastUpdate : QDateTime{QDate{0, 0, 0}, QTime{0, 0}});

    sendToServer(static_cast<AbduMessagePtr>(syncMessages));
}

void NetworkHandler::sendRegisterRequest(const QString &firstName,
                                         const QString &lastName,
                                         const QString &username,
                                         const QString &email,
                                         const QString &phone,
                                         const QString &password)
{
    AnyMessagePtr<RegisterMessage> registerMessage{new RegisterMessage};
    registerMessage->setFirstName(firstName);
    registerMessage->setLastName(lastName);
    registerMessage->setUsername(username);
    registerMessage->setEmail(email);
    registerMessage->setPhone(phone);
    registerMessage->setPassword(password);

    sendToServer(static_cast<AbduMessagePtr>(registerMessage));
}
