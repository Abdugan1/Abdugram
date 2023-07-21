#ifndef FOUNDUSERCHATITEM_H
#define FOUNDUSERCHATITEM_H

#include "chatmodelitem.h"

#include <QUrl>

class FoundUserItem : public ChatModelItem
{
public:
    enum Roles {
        UserId = ChatModelItem::Roles::UserRole + 1,
        PictureUrl,
        Username,
    };

    explicit FoundUserItem();

    int userId() const;
    void setUserId(int newUserId);

    QUrl pictureUrl() const;
    void setPictureUrl(const QUrl &newPictureUrl);

    QString userName() const;
    void setUserName(const QString &newUserName);

protected:
    QVariant dataImp(int role) const override;

private:
    int userId_ = -1;
    QUrl pictureUrl_;
    QString userName_;
};

#endif // FOUNDUSERCHATITEM_H
