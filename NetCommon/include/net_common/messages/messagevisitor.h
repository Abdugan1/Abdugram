#ifndef MESSAGEVISITOR_H
#define MESSAGEVISITOR_H

#include "../NetCommon_global.h"

#include "messagesforwarddeclaration.h"

class NETCOMMON_EXPORT MessageVisitor
{
public:
    explicit MessageVisitor() = default;
    virtual ~MessageVisitor() {};

    virtual void visit(const LoginMessage&          message) { Q_UNUSED(message); }
    virtual void visit(const RegisterMessage&       message) { Q_UNUSED(message); }
    virtual void visit(const SyncChatsRequest&      message) { Q_UNUSED(message); }
    virtual void visit(const SearchOnServerMessage& message) { Q_UNUSED(message); }
    virtual void visit(const CreateChatMessage&     message) { Q_UNUSED(message); }
    virtual void visit(const SendMessageMessage&    message) { Q_UNUSED(message); }

    virtual void visit(const RegisterStatusMessage&    message) { Q_UNUSED(message); }
    virtual void visit(const LoginStatusMessage&       message) { Q_UNUSED(message); }
    virtual void visit(const SearchUsersResultMessage& message) { Q_UNUSED(message); }
    virtual void visit(const CreateChatResultMessage&  message) { Q_UNUSED(message); }
    virtual void visit(const SendMessageResultMessage& message) { Q_UNUSED(message); }

};

//MessageVisitor::~MessageVisitor() {}

#endif // MESSAGEVISITOR_H
