#ifndef SERVERMESSAGEVISITOR_H
#define SERVERMESSAGEVISITOR_H

#include <net_common/messages/messagevisitor.h>

class NetworkHandler;
class Session;

class ServerMessageVisitor : public MessageVisitor
{
public:
    explicit ServerMessageVisitor(NetworkHandler *networkHandler, Session *client);
    ~ServerMessageVisitor() {};
    
    void visit(const LoginRequest        &request) override;
    void visit(const RegisterRequest     &request) override;
    void visit(const SyncUsersRequest    &request) override;
    void visit(const SyncChatsRequest    &request) override;
    void visit(const SyncMessagesRequest &request) override;
    void visit(const SearchRequest       &request) override;
    void visit(const CreateChatRequest   &request) override;
    void visit(const SendMessageRequest  &request) override;
    void visit(const LogoutRequest       &request) override;

private:
    NetworkHandler *networkHandler_ = nullptr;
    Session        *client_ = nullptr;

};

#endif // SERVERMESSAGEVISITOR_H
