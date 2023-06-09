#ifndef SERVERMESSAGEVISITOR_H
#define SERVERMESSAGEVISITOR_H

#include <net_common/messages/messagevisitor.h>

class Server;
class Session;

class ServerMessageVisitor : public MessageVisitor
{
public:
    explicit ServerMessageVisitor(Server *server, Session *client);

    void visit(const RegisterMessage          &message) override;
    void visit(const LoginMessage             &message) override;
    void visit(const RegisterStatusMessage    &message) override;
    void visit(const LoginStatusMessage       &message) override;
    void visit(const SyncChatsRequest         &message) override;
    void visit(const SearchOnServerMessage    &message) override;
    void visit(const SearchUsersResultMessage &message) override;
    void visit(const CreateChatMessage        &message) override;
    void visit(const CreateChatResultMessage &message) override;

private:
    Server   *server_ = nullptr;
    Session  *client_ = nullptr;
};

#endif // SERVERMESSAGEVISITOR_H
