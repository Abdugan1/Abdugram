#ifndef ISUSERNAMEFREEREQUEST_H
#define ISUSERNAMEFREEREQUEST_H

#include "abdumessage.h"

class NETCOMMON_EXPORT IsUsernameFreeRequest : public AbduMessage
{
public:
    explicit IsUsernameFreeRequest();

    void accept(MessageVisitor *visitor) const override;

    QString username() const;
    void setUsername(const QString &newUsername);

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    QString username_;
};

#endif // ISUSERNAMEFREEREQUEST_H
