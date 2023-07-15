#ifndef MESSAGEMODELITEM_H
#define MESSAGEMODELITEM_H

#include <QVariant>

class MessageModelItem
{
public:
    enum class Roles {
        Type =  Qt::UserRole + 1,

        UserRole,
    };

    enum class Type : int {
        Unknown = -1,
        MessageItem,
        DateSeparatorItem,
    };

    explicit MessageModelItem(Type type);
    virtual ~MessageModelItem() = default;

    QVariant data(int role) const;

    Type type() const;
protected:
    virtual QVariant dataImp(int role) const = 0;

private:
    Type type_ = Type::Unknown;
};

#endif // MESSAGEMODELITEM_H
