#ifndef REGISTERREPLY_H
#define REGISTERREPLY_H

#include "abdumessage.h"

#include <sql_common/data_structures/user.h>

class NETCOMMON_EXPORT RegisterReply : public AbduMessage
{
public:
    explicit RegisterReply();

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

#endif // REGISTERREPLY_H
