#include "net/server.h"
#include "net/networkhandler.h"
#include "net/servermessagevisitor.h"
#include "net/session.h"

#include <net_common/consts.h>

#include <sql_server/databaseserver.h>

#include <QHostAddress>
#include <QDebug>

Server::Server(QObject *parent)
    : QTcpServer{parent}
    , threadPool_{new ThreadPool}
    , networkHandler_{new NetworkHandler{this}}
{
}

Server::~Server()
{
    stop();
}

void Server::connectToDatabase()
{
    DatabaseServer::instance()->connectToDatabase();
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
    emit logCreated("Server stopped");
}

void Server::toggle()
{
    if (isListening())
        stop();
    else
        start();
}

void Server::processMessage(const AbduMessagePtr &message)
{
    auto client = qobject_cast<Session *>(sender());
    ServerMessageVisitor messageVisitor_{networkHandler_, client};
    message->accept(&messageVisitor_);

    emit logCreated(QString::fromUtf8(message->toData()));
}

void Server::onClientDisconected()
{
    auto session = qobject_cast<Session *>(sender());
    if (session->userId() > 0) {
        networkHandler_->removeSession(session->userId());
    }
    session->deleteLater();
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    TcpSession *session = createSession();

    bool opened;
    QMetaObject::invokeMethod(session, "openSession", Qt::BlockingQueuedConnection, Q_RETURN_ARG(bool, opened), Q_ARG(quintptr, socketDescriptor));

    if (!opened) {
        session->deleteLater();
        return;
    }

    QString log = "New session created: " + session->peerAddress().toString();
    emit logCreated(log);
}

Session *Server::createSession()
{
    Session *session = new Session;
    threadPool_->moveObjectToLeastLoadedThread(session);

    connect(session, &Session::received, this, &Server::processMessage);

    // cleaning
    connect(this,    &Server::aboutToStop,   session, &TcpSession::closeSession);
    connect(session, &Session::disconnected, this,    &Server::onClientDisconected);

    return session;
}

