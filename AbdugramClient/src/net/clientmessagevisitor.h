#ifndef CLIENTMESSAGEVISITOR_H
#define CLIENTMESSAGEVISITOR_H

#include <net_common/messages/messagevisitor.h>

class NetworkHandler;

class ClientMessageVisitor : public MessageVisitor
{
public:
    explicit ClientMessageVisitor();

    void visit(const RegisterMessage          &message) override;
    void visit(const LoginMessage             &message) override;
    void visit(const RegisterStatusMessage    &message) override;
    void visit(const LoginStatusMessage       &message) override;
    void visit(const SyncChatsRequest         &message) override;
    void visit(const SearchOnServerMessage    &message) override;
    void visit(const SearchUsersResultMessage &mesasge) override;
    void visit(const CreateChatMessage        &message) override;
    void visit(const CreateChatResultMessage  &message) override;
};

#endif // CLIENTMESSAGEVISITOR_H
