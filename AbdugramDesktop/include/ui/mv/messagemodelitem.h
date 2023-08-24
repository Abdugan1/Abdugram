#ifndef MESSAGEMODELITEM_H
#define MESSAGEMODELITEM_H

#include <QVariant>

class MessageModelItem
{
public:
    enum Roles {
        Type =  Qt::UserRole + 1,

        UserRole,
    };

    enum  Type : int {
        Unknown = -1,
        MessageItem,
        DateSeparatorItem,
    };

    explicit MessageModelItem(enum Type type);
    virtual ~MessageModelItem() = default;

    QVariant data(int role) const;
    virtual void setData(int role, const QVariant &data) = 0;

    enum Type type() const;
protected:
    virtual QVariant dataImp(int role) const = 0;

private:
    enum Type type_ = Type::Unknown;
};

#endif // MESSAGEMODELITEM_H
