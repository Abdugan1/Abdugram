#ifndef REGISTERSTATUSMESSAGE_H
#define REGISTERSTATUSMESSAGE_H

#include "abdumessage.h"

class NETCOMMON_EXPORT RegisterStatusMessage : public AbduMessage
{
public:
    explicit RegisterStatusMessage();

    bool success() const;
    void setSuccess(bool newSuccess);

    void accept(MessageVisitor *visitor) const override;

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    bool success_ = false;

};

#endif // REGISTERSTATUSMESSAGE_H
