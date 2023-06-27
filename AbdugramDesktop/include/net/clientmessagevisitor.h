#ifndef CLIENTMESSAGEVISITOR_H
#define CLIENTMESSAGEVISITOR_H

#include <net_common/messages/messagevisitor.h>

class NetworkHandler;

class ClientMessageVisitor : public MessageVisitor
{
public:
    explicit ClientMessageVisitor() = default;
    ~ClientMessageVisitor() {};
    
    void visit(const LoginReply       &message) override;
    void visit(const RegisterReply    &message) override;
    void visit(const SyncUsersReply           &reply)   override;
    void visit(const SyncChatsReply           &reply)   override;
    void visit(const SyncMessagesReply        &reply)   override;
    void visit(const SearchUsersReply &mesasge) override;
    void visit(const CreateChatReply  &message) override;
    void visit(const SendMessageReply &message) override;
};

#endif // CLIENTMESSAGEVISITOR_H
