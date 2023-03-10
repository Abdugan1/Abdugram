#include "server.h"

#include <net_common/consts.h>
#include <net_common/tcpsession.h>
#include <net_common/messages/registermessage.h>

#include <QHostAddress>
#include <QDebug>

Server::Server(QObject *parent)
    : QTcpServer{parent}
    , threadPool_{new ThreadPool}
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
    if (auto registerMessage = dynamic_cast<const RegisterMessage*>(message.data())) {
        qDebug() << "Success conversion";
        qDebug() << "firstname" << registerMessage->firstName();
        qDebug() << "lastname" << registerMessage->lastName();
    } else {
        qDebug() << "Failed to converse";
    }
    emit logCreated(QString::fromUtf8(message->toData()));
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

TcpSession *Server::createSession()
{
    TcpSession *session = new TcpSession;
    threadPool_->moveObjectToLeastLoadedThread(session);

    qDebug() << "rec con:" << connect(session, &TcpSession::received, this, &Server::processMessage);

    // cleaning
    connect(this,    &Server::aboutToStop,      session, &TcpSession::closeSession);
    connect(session, &TcpSession::disconnected, session, &TcpSession::deleteLater);


    return session;
}
