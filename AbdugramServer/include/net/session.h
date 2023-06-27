#ifndef SESSION_H
#define SESSION_H

#include <net_common/tcpsession.h>

class Session : public TcpSession
{
    Q_OBJECT
public:
    explicit Session(QObject *parent = nullptr);

    int userId() const;
    void setUserId(int newUserId);

private:
    int userId_ = -1;
};

#endif // SESSION_H
