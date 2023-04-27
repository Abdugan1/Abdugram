#include "clientmessagevisitor.h"
#include "ui/mainwindow.h"

#include <net_common/messages/registerstatusmessage.h>
#include <net_common/messages/loginstatusmessage.h>
#include <net_common/messages/searchusersresultmessage.h>

#include <data_structures/user.h>

#include <QDebug>

ClientMessageVisitor::ClientMessageVisitor(MainWindow *mainWindow)
    : mainWindow_{mainWindow}
{
}

void ClientMessageVisitor::visit(const RegisterMessage &message)
{
    Q_UNUSED(message);
}

void ClientMessageVisitor::visit(const LoginMessage &message)
{
    Q_UNUSED(message);
}

void ClientMessageVisitor::visit(const RegisterStatusMessage &message)
{
    qDebug() << "success registration?" << message.success();
}

void ClientMessageVisitor::visit(const LoginStatusMessage &message)
{
    qDebug() << "Success login?" << message.success();
    if (message.success()) {
        mainWindow_->toMainPage();
    } else {
    }
}

void ClientMessageVisitor::visit(const SyncChatsRequest &message)
{

}

void ClientMessageVisitor::visit(const SearchOnServerMessage &message)
{
    Q_UNUSED(message);
}

void ClientMessageVisitor::visit(const SearchUsersResultMessage &message)
{
    const QList<User> users = message.users();
    for (const auto& user : users) {
        qDebug() << "username:" << user.username();
    }
}
