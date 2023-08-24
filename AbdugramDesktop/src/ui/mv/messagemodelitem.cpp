#include "ui/mv/messagemodelitem.h"

MessageModelItem::MessageModelItem(enum Type type)
    : type_{type}
{
}

QVariant MessageModelItem::data(int role) const
{
    if (role == Roles::Type) {
        return type();
    }

    return dataImp(role);
}

enum MessageModelItem::Type MessageModelItem::type() const
{
    return type_;
}
