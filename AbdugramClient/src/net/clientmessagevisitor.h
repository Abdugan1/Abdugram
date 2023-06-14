#ifndef CLIENTMESSAGEVISITOR_H
#define CLIENTMESSAGEVISITOR_H

#include <net_common/messages/messagevisitor.h>

class NetworkHandler;

class ClientMessageVisitor : public MessageVisitor
{
public:
    explicit ClientMessageVisitor() = default;
    ~ClientMessageVisitor() {};

    void visit(const RegisterStatusMessage    &message) override;
    void visit(const LoginStatusMessage       &message) override;
    void visit(const SearchUsersResultMessage &mesasge) override;
    void visit(const CreateChatResultMessage  &message) override;
    void visit(const SendMessageResultMessage &message) override;
};

#endif // CLIENTMESSAGEVISITOR_H
