#include "tcpsession.h"

TcpSession::TcpSession(QObject *parent)
    : QTcpSocket{parent}
{

}

bool TcpSession::open(quintptr descriptor)
{
    if (!setSocketDescriptor(descriptor)) {
        return false;
    }

    return true;
}
