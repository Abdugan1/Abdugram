#ifndef MESSAGEVISITOR_H
#define MESSAGEVISITOR_H

#include "../NetCommon_global.h"

#include "messagesforwarddeclaration.h"

class NETCOMMON_EXPORT MessageVisitor
{
public:
    explicit MessageVisitor() = default;
    virtual ~MessageVisitor() {};
    
    virtual void visit(const LoginRequest        &request) { Q_UNUSED(request); }
    virtual void visit(const RegisterRequest     &request) { Q_UNUSED(request); }
    virtual void visit(const SyncUsersRequest    &request) { Q_UNUSED(request); }
    virtual void visit(const SyncChatsRequest    &request) { Q_UNUSED(request); }
    virtual void visit(const SyncMessagesRequest &request) { Q_UNUSED(request); }
    virtual void visit(const SearchRequest       &request) { Q_UNUSED(request); }
    virtual void visit(const CreateChatRequest   &request) { Q_UNUSED(request); }
    virtual void visit(const SendMessageRequest  &request) { Q_UNUSED(request); }
    
    virtual void visit(const LoginReply        &reply) { Q_UNUSED(reply); }
    virtual void visit(const RegisterReply     &reply) { Q_UNUSED(reply); }
    virtual void visit(const SyncUsersReply    &reply) { Q_UNUSED(reply); }
    virtual void visit(const SyncChatsReply    &reply) { Q_UNUSED(reply); }
    virtual void visit(const SyncMessagesReply &reply) { Q_UNUSED(reply); }
    virtual void visit(const SearchUsersReply  &reply) { Q_UNUSED(reply); }
    virtual void visit(const CreateChatReply   &reply) { Q_UNUSED(reply); }
    virtual void visit(const SendMessageReply  &reply) { Q_UNUSED(reply); }

};

//MessageVisitor::~MessageVisitor() {}

#endif // MESSAGEVISITOR_H
