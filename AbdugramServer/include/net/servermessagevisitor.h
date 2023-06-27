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
    
    void visit(const LoginRequest          &message) override;
    void visit(const RegisterRequest       &message) override;
    void visit(const SyncUsersRequest      &message) override;
    void visit(const SyncChatsRequest      &request) override;
    void visit(const SyncMessagesRequest   &request) override;
    void visit(const SearchRequest &message) override;
    void visit(const CreateChatRequest     &message) override;
    void visit(const SendMessageRequest    &message) override;

private:
    NetworkHandler *networkHandler_ = nullptr;
    TcpSession     *client_ = nullptr;
};

#endif // SERVERMESSAGEVISITOR_H
