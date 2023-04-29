#include "networkhandler.h"
#include "clientmessagevisitor.h"

#include <net_common/messages/abdumessage.h>
#include <net_common/consts.h>

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
    tcpSession_->send(message);
}

void NetworkHandler::onMessageReceived(const AbduMessagePtr &message)
{
    ClientMessageVisitor visitor{this};
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

