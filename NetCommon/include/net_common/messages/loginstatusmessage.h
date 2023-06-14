#ifndef LOGINSTATUSMESSAGE_H
#define LOGINSTATUSMESSAGE_H

#include "abdumessage.h"

#include <sql_common/data_structures/user.h>

class NETCOMMON_EXPORT LoginStatusMessage : public AbduMessage
{
public:
    explicit LoginStatusMessage();

    bool success() const;
    void setSuccess(bool newSuccess);

    User user() const;
    void setUser(const User &newUser);

    void accept(MessageVisitor *visitor) const override;

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    bool success_ = false;
    User user_;

};

#endif // LOGINSTATUSMESSAGE_H
