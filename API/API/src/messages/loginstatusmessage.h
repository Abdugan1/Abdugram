#ifndef LOGINSTATUSMESSAGE_H
#define LOGINSTATUSMESSAGE_H

#include "abdumessage.h"

class LoginStatusMessage : public AbduMessage
{
public:
    explicit LoginStatusMessage();

    void fromData(const QByteArray &data) override;
    QByteArray toData() const override;

    bool success() const;
    void setSuccess(bool newSuccess);

private:
    bool success_ = false;

};

#endif // LOGINSTATUSMESSAGE_H
