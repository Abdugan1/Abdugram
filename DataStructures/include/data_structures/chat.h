#ifndef CHAT_H
#define CHAT_H

#include <QString>
#include <QDateTime>

class Chat
{
public:
    explicit Chat();

    int id() const;
    void setId(int newId);

    QString name() const;
    void setName(const QString &newName);

    int createdByUserId() const;
    void setCreatedByUserId(int newCreatedByUserId);

private:
    int id_ = -1;
    QString name_;
    int createdByUserId_ = -1;

};

#endif // CHAT_H
