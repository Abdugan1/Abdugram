#ifndef REGISTERMESSAGE_H
#define REGISTERMESSAGE_H

#include "abdumessage.h"

class NETCOMMON_EXPORT RegisterMessage : public AbduMessage
{
public:
    explicit RegisterMessage();

    QByteArray toData() const override;

    QString firstName() const;
    void setFirstName(const QString &newFirstName);

    QString lastName() const;
    void setLastName(const QString &newLastName);

    QString username() const;
    void setUsername(const QString &newUsername);

    QString password() const;
    void setPassword(const QString &newPassword);

    QString phone() const;
    void setPhone(const QString &newPhoneNumber);

    QString email() const;
    void setEmail(const QString &newEmail);

private:
    void gainDataFromPayload(DataStream *stream) override;

private:
    QString firstName_;
    QString lastName_;
    QString username_;
    QString password_;
    QString phone_;
    QString email_;
};

#endif // REGISTERMESSAGE_H
