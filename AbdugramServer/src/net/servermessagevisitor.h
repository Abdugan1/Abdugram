#ifndef SERVERMESSAGEVISITOR_H
#define SERVERMESSAGEVISITOR_H

#include <net_common/messages/messagevisitor.h>

class Server;
class TcpSession;

class ServerMessageVisitor : public MessageVisitor
{
public:
    explicit ServerMessageVisitor(Server *server, TcpSession *client);

    void visit(const RegisterMessage          &message) override;
    void visit(const LoginMessage             &message) override;
    void visit(const RegisterStatusMessage    &message) override;
    void visit(const LoginStatusMessage       &message) override;
    void visit(const SyncChatsRequest         &message) override;
    void visit(const SearchOnServerMessage    &message) override;
    void visit(const SearchUsersResultMessage &message) override;

private:
    Server      *server_ = nullptr;
    TcpSession  *client_ = nullptr;

};

#endif // SERVERMESSAGEVISITOR_H
