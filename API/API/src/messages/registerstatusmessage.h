#ifndef REGISTERSTATUSMESSAGE_H
#define REGISTERSTATUSMESSAGE_H

#include "abdumessage.h"

class RegisterStatusMessage : public AbduMessage
{
public:
    explicit RegisterStatusMessage();

    void fromData(const QByteArray &data) override;
    QByteArray toData() const override;

    bool success() const;
    void setSuccess(bool newSuccess);

private:
    bool success_ = false;
};

#endif // REGISTERSTATUSMESSAGE_H
