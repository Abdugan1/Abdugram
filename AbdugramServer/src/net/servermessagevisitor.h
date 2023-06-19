#ifndef SERVERMESSAGEVISITOR_H
#define SERVERMESSAGEVISITOR_H

#include <net_common/messages/messagevisitor.h>

class NetworkHandler;
class TcpSession;

class ServerMessageVisitor : public MessageVisitor
{
public:
    explicit ServerMessageVisitor(NetworkHandler *networkHandler, TcpSession *client);
    ~ServerMessageVisitor() {};

    void visit(const LoginMessage          &message) override;
    void visit(const RegisterMessage       &message) override;
    void visit(const SyncUsersMessage      &message) override;
    void visit(const SyncChatsRequest      &message) override;
    void visit(const SearchOnServerMessage &message) override;
    void visit(const CreateChatMessage     &message) override;
    void visit(const SendMessageMessage    &message) override;

private:
    NetworkHandler *networkHandler_ = nullptr;
    TcpSession     *client_ = nullptr;

};

#endif // SERVERMESSAGEVISITOR_H
