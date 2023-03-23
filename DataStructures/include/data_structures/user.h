#ifndef USER_H
#define USER_H

#include "DataStructures_global.h"

#include <QString>

class DATASTRUCTURES_EXPORT User
{
public:
    explicit User();

    int id() const;
    void setId(int newId);

    QString username() const;
    void setUsername(const QString &newUsername);

    QString firstName() const;
    void setFirstName(const QString &newFirstName);

    QString lastName() const;
    void setLastName(const QString &newLastName);

    QString email() const;
    void setEmail(const QString &newEmail);

    QString phone() const;
    void setPhone(const QString &newPhone);

private:
    int id_ = -1;
    QString username_;
    QString firstName_;
    QString lastName_;
    QString email_;
    QString phone_;
};

#endif // USER_H
