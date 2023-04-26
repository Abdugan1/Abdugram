#include "chat.h"

Chat::Chat()
{

}

int Chat::id() const
{
    return id_;
}

void Chat::setId(int newId)
{
    id_ = newId;
}

QString Chat::name() const
{
    return name_;
}

void Chat::setName(const QString &newName)
{
    name_ = newName;
}

int Chat::createdByUserId() const
{
    return createdByUserId_;
}

void Chat::setCreatedByUserId(int newCreatedByUserId)
{
    createdByUserId_ = newCreatedByUserId;
}
