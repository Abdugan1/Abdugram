#ifndef LOGINSTATUSMESSAGE_H
#define LOGINSTATUSMESSAGE_H

#include "abdumessage.h"

class NETCOMMON_EXPORT LoginStatusMessage : public AbduMessage
{
public:
    explicit LoginStatusMessage();

    bool success() const;
    void setSuccess(bool newSuccess);

    int userId() const;
    void setUserId(int newUserId);

    void accept(MessageVisitor *visitor) const override;

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    bool success_ = false;
    int  userId_  = -1;

};

#endif // LOGINSTATUSMESSAGE_H
