#ifndef LOGINSTATUSMESSAGE_H
#define LOGINSTATUSMESSAGE_H

#include "abdumessage.h"

class NETCOMMON_EXPORT LoginStatusMessage : public AbduMessage
{
public:
    explicit LoginStatusMessage();

    QByteArray toData() const override;

    bool success() const;
    void setSuccess(bool newSuccess);

    void accept(MessageVisitor *visitor) const override;

private:
    void gainDataFromPayload(DataStream *stream) override;

private:
    bool success_ = false;
};

#endif // LOGINSTATUSMESSAGE_H
