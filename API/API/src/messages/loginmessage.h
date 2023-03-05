#ifndef LOGINMESSAGE_H
#define LOGINMESSAGE_H

#include "abdumessage.h"

class LoginMessage : public AbduMessage
{
public:
    explicit LoginMessage();

    QString username() const;
    void setUsername(const QString &newUsername);

    QString password() const;
    void setPassword(const QString &newPassword);

    QByteArray toData() const override;

private:
    void gainDataFromPayload(DataStream *stream) override;

private:
    QString username_;
    QString password_;

};

#endif // LOGINMESSAGE_H
