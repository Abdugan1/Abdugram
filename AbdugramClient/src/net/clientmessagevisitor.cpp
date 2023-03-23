#include "clientmessagevisitor.h"

#include <net_common/messages/registerstatusmessage.h>
#include <net_common/messages/loginstatusmessage.h>

#include <QDebug>

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
}
