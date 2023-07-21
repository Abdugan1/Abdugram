#ifndef LINESEPARATORITEM_H
#define LINESEPARATORITEM_H

#include "chatmodelitem.h"

class LineSeparatorItem : public ChatModelItem
{
public:
    explicit LineSeparatorItem();

protected:
    QVariant dataImp(int role) const override;
};

#endif // LINESEPARATORITEM_H
