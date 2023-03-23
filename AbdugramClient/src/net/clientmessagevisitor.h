#ifndef CLIENTMESSAGEVISITOR_H
#define CLIENTMESSAGEVISITOR_H

#include <net_common/messages/messagevisitor.h>

class ClientMessageVisitor : public MessageVisitor
{
public:
    explicit  ClientMessageVisitor() = default;

    void visit(const RegisterMessage &message) override;
    void visit(const LoginMessage &message) override;
    void visit(const RegisterStatusMessage &message) override;
    void visit(const LoginStatusMessage &message) override;
};

#endif // CLIENTMESSAGEVISITOR_H
