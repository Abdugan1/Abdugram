#include "ui/mv/lineseparatoritem.h"

LineSeparatorItem::LineSeparatorItem()
    : ChatModelItem{Type::LineSeparator}
{

}

QVariant LineSeparatorItem::dataImp(int role) const
{
    return QVariant{};
}
