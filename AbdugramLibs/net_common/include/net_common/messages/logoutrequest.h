#ifndef LOGOUTREQUEST_H
#define LOGOUTREQUEST_H

#include "abdumessage.h"

class NETCOMMON_EXPORT LogoutRequest : public AbduMessage
{
public:
    explicit LogoutRequest();

    void accept(MessageVisitor *visitor) const override;

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;
};

#endif // LOGOUTREQUEST_H
