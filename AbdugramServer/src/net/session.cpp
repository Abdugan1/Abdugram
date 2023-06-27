#include "net/session.h"

Session::Session(QObject *parent)
    : TcpSession{parent}
{

}

int Session::userId() const
{
    return userId_;
}

void Session::setUserId(int newUserId)
{
    userId_ = newUserId;
}
