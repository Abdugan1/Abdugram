#ifndef MESSAGEVISITOR_H
#define MESSAGEVISITOR_H

#include "../NetCommon_global.h"

#include "messagesforwarddeclaration.h"

class NETCOMMON_EXPORT MessageVisitor
{
public:
    explicit MessageVisitor() = default;
    virtual ~MessageVisitor() = default;

    virtual void visit(const RegisterMessage                &message) = 0;
    virtual void visit(const LoginMessage                   &message) = 0;
    virtual void visit(const RegisterStatusMessage          &message) = 0;
    virtual void visit(const LoginStatusMessage             &message) = 0;
    virtual void visit(const SyncChatsRequest               &message) = 0;
    virtual void visit(const SearchOnServerMessage          &message) = 0;
    virtual void visit(const SearchUsersResultMessage       &message) = 0;
    virtual void visit(const CreatePrivateChatMessage       &message) = 0;
    virtual void visit(const CreatePrivateChatResultMessage &message) = 0;
};

#endif // MESSAGEVISITOR_H
