#include "server.h"
#include "consts.h"
#include "tcpsession.h"

#include <QHostAddress>
#include <QDebug>

Server::Server(QObject *parent)
    : QTcpServer{parent}
{

}

Server::~Server()
{
    stop();
}

void Server::start()
{
    if (isListening())
        return;

    if (!listen(QHostAddress::Any, consts::server::Port)) {
        QString log = "Couldn't start server! " + errorString();
        qCritical() << log;
        emit logCreated(log);
        return;
    }

    emit started();
    emit logCreated("Server started");
}

void Server::stop()
{
    if (!isListening())
        return;

    emit aboutToStop();

    close();

    emit stopped();
    emit logCreated("Server stopeed");
}

void Server::toggle()
{
    if (isListening())
        stop();
    else
        start();
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    TcpSession *session = createSession();
    if (!session->openSession(socketDescriptor)) {
        session->deleteLater();
    }

    connect(session, &TcpSession::disconnected, session, &TcpSession::deleteLater);

    QString log = "New session created: " + session->peerAddress().toString();
    emit logCreated(log);
}

TcpSession *Server::createSession()
{
    TcpSession *session = new TcpSession;

    // cleaning
    connect(this,    &Server::aboutToStop,      session, &TcpSession::deleteLater);
    connect(session, &TcpSession::disconnected, session, &TcpSession::deleteLater);

    threadPool_.moveObjectToLeastLoadedThread(session);

    return session;
}
