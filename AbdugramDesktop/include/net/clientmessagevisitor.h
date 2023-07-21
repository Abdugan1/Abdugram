#ifndef CLIENTMESSAGEVISITOR_H
#define CLIENTMESSAGEVISITOR_H

#include <net_common/messages/messagevisitor.h>

class NetworkHandler;

class ClientMessageVisitor : public MessageVisitor
{
public:
    explicit ClientMessageVisitor() = default;
    ~ClientMessageVisitor() {};
    
    void visit(const LoginReply        &reply) override;
    void visit(const RegisterReply     &reply) override;
    void visit(const SyncUsersReply    &reply) override;
    void visit(const SyncChatsReply    &reply) override;
    void visit(const SyncMessagesReply &reply) override;
    void visit(const SearchUsersReply  &reply) override;
    void visit(const CreateChatReply   &reply) override;
    void visit(const SendMessageReply  &reply) override;
    void visit(const LogoutReply       &reply) override;
};

#endif // CLIENTMESSAGEVISITOR_H
