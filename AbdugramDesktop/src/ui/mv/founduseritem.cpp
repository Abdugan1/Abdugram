#include "ui/mv/founduseritem.h"

FoundUserItem::FoundUserItem()
    : ChatModelItem{Type::FoundUserItem}
{

}

int FoundUserItem::userId() const
{
    return userId_;
}

void FoundUserItem::setUserId(int newUserId)
{
    userId_ = newUserId;
}

QUrl FoundUserItem::pictureUrl() const
{
    return pictureUrl_;
}

void FoundUserItem::setPictureUrl(const QUrl &newPictureUrl)
{
    pictureUrl_ = newPictureUrl;
}

QString FoundUserItem::userName() const
{
    return userName_;
}

void FoundUserItem::setUserName(const QString &newUserName)
{
    userName_ = newUserName;
}

QVariant FoundUserItem::dataImp(int role) const
{
    switch (role) {
    case Roles::UserId: return userId_;         break;
    case Roles::PictureUrl: return pictureUrl_; break;
    case Roles::Username:   return userName_;   break;
    }
    return QVariant{};
}
