#ifndef DATESEPARATORITEM_H
#define DATESEPARATORITEM_H

#include "messagemodelitem.h"

#include <QDate>

class DateSeparatorItem : public MessageModelItem
{
public:
    enum Roles {
        Date = static_cast<int>(MessageModelItem::Roles::UserRole) + 1
    };

    explicit DateSeparatorItem(const QDate &date);

    QDate date() const;
    void setDateTime(const QDate &newDate);

protected:
    QVariant dataImp(int role) const override;

private:
    QDate date_;
};

#endif // DATESEPARATORITEM_H
