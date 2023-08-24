#include "ui/mv/dateseparatoritem.h"

#include <QVariant>
#include <QDebug>

DateSeparatorItem::DateSeparatorItem(const QDate &date)
    : MessageModelItem{Type::DateSeparatorItem}
    , date_{date}
{
}

QDate DateSeparatorItem::date() const
{
    return date_;
}

void DateSeparatorItem::setDateTime(const QDate &newDate)
{
    date_ = newDate;
}

void DateSeparatorItem::setData(int role, const QVariant &data)
{
    Q_UNREACHABLE();
}

QVariant DateSeparatorItem::dataImp(int role) const
{
    switch (static_cast<Roles>(role)) {
    case Roles::Date: return date_; break;
    }
    return QVariant{};
}
