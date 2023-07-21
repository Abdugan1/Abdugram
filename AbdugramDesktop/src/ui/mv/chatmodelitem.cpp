#include "ui/mv/chatmodelitem.h"

ChatModelItem::ChatModelItem(enum Type type)
    : type_{type}
{

}

QVariant ChatModelItem::data(int role) const
{
    if (role == Roles::Type) {
        return static_cast<int>(type());
    }

    return dataImp(role);
}

enum ChatModelItem::Type ChatModelItem::type() const
{
    return type_;
}
