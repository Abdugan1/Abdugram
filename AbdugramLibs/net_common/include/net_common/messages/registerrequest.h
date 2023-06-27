#ifndef REGISTERREQUEST_H
#define REGISTERREQUEST_H

#include "abdumessage.h"

class NETCOMMON_EXPORT RegisterRequest : public AbduMessage
{
public:
    explicit RegisterRequest();

    QString firstName() const;
    void setFirstName(const QString &newFirstName);

    QString username() const;
    void setUsername(const QString &newUsername);

    QString password() const;
    void setPassword(const QString &newPassword);

    QString phone() const;
    void setPhone(const QString &newPhoneNumber);

    QString email() const;
    void setEmail(const QString &newEmail);

    void accept(MessageVisitor *visitor) const override;

protected:
    void getBodyData(DataStream *stream) override;
    void writeBodyData(DataStream *stream) const override;

private:
    QString firstName_;
    QString username_;
    QString password_;
    QString phone_;
    QString email_;

};

#endif // REGISTERREQUEST_H
