#ifndef MESSAGEVISITOR_H
#define MESSAGEVISITOR_H

#include "../NetCommon_global.h"

#include "messagesforwarddeclaration.h"

class NETCOMMON_EXPORT MessageVisitor
{
public:
    explicit MessageVisitor() = default;
    virtual ~MessageVisitor() {};

    virtual void visit(const LoginMessage           &request) { Q_UNUSED(request); }
    virtual void visit(const RegisterMessage        &request) { Q_UNUSED(request); }
    virtual void visit(const SyncUsersMessage       &request) { Q_UNUSED(request); }
    virtual void visit(const SyncChatsRequest       &request) { Q_UNUSED(request); }
    virtual void visit(const SyncMessagesRequest    &request) { Q_UNUSED(request); }
    virtual void visit(const SearchOnServerMessage  &request) { Q_UNUSED(request); }
    virtual void visit(const CreateChatMessage      &request) { Q_UNUSED(request); }
    virtual void visit(const SendMessageMessage     &request) { Q_UNUSED(request); }

    virtual void visit(const LoginStatusMessage        &reply) { Q_UNUSED(reply); }
    virtual void visit(const RegisterStatusMessage     &reply) { Q_UNUSED(reply); }
    virtual void visit(const SyncUsersReply            &reply) { Q_UNUSED(reply); }
    virtual void visit(const SyncChatsReply            &reply) { Q_UNUSED(reply); }
    virtual void visit(const SyncMessagesReply         &reply) { Q_UNUSED(reply); }
    virtual void visit(const SearchUsersResultMessage  &reply) { Q_UNUSED(reply); }
    virtual void visit(const CreateChatResultMessage   &reply) { Q_UNUSED(reply); }
    virtual void visit(const SendMessageResultMessage  &reply) { Q_UNUSED(reply); }

};

//MessageVisitor::~MessageVisitor() {}

#endif // MESSAGEVISITOR_H
