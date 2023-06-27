#ifndef LOGINREPLY_H
#define LOGINREPLY_H

#include "abdumessage.h"

#include <sql_common/data_structures/user.h>

class NETCOMMON_EXPORT LoginReply : public AbduMessage
{
public:
    explicit LoginReply();

    bool success() const;
    void setSuccess(bool newSuccess);

    void accept(MessageVisitor *visitor) const override;

    User user() const;
    void setUser(const User &newUser);

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    bool success_ = false;
    User user_;
};

#endif // LOGINREPLY_H
