#include "server.h"
#include "consts.h"

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
        qCritical() << "Couldn't start server!" << errorString();
        return;
    }

    emit started();
    qInfo() << "Server started";
}

void Server::stop()
{
    if (!isListening())
        return;

    close();

    emit stopped();
    qInfo() << "Server stopeed";
}

void Server::incomingConnection(qintptr handle)
{

}
