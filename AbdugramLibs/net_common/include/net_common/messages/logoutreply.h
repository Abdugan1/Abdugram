#ifndef LOGOUTREPLY_H
#define LOGOUTREPLY_H

#include "abdumessage.h"

class LogoutReply : public AbduMessage
{
public:
    explicit LogoutReply();

    void accept(MessageVisitor *visitor) const override;

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;
};

#endif // LOGOUTREPLY_H
