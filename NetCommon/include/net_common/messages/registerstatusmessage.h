#ifndef REGISTERSTATUSMESSAGE_H
#define REGISTERSTATUSMESSAGE_H

#include "abdumessage.h"

class NETCOMMON_EXPORT RegisterStatusMessage : public AbduMessage
{
public:
    explicit RegisterStatusMessage();

    QByteArray toData() const override;

    bool success() const;
    void setSuccess(bool newSuccess);

private:
    void gainDataFromPayload(DataStream *stream) override;

private:
    bool success_ = false;

};

#endif // REGISTERSTATUSMESSAGE_H
