#ifndef ISUSERNAMEFREEREPLY_H
#define ISUSERNAMEFREEREPLY_H

#include "abdumessage.h"

class NETCOMMON_EXPORT IsUsernameFreeReply : public AbduMessage
{
public:
    explicit IsUsernameFreeReply();

    void accept(MessageVisitor *visitor) const override;

    bool isFree() const;
    void setIsFree(bool newIsFree);

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    bool isFree_ = false;
};

#endif // ISUSERNAMEFREEREPLY_H
