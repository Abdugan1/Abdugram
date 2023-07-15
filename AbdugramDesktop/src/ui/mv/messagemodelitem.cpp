#include "ui/mv/messagemodelitem.h"

MessageModelItem::MessageModelItem(Type type)
    : type_{type}
{
}

QVariant MessageModelItem::data(int role) const
{
    if (role == static_cast<int>(Roles::Type)) {
        return static_cast<int>(type());
    }

    return dataImp(role);
}

MessageModelItem::Type MessageModelItem::type() const
{
    return type_;
}
