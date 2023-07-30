#include "ui/mv/sectionseparator.h"

SectionSeparator::SectionSeparator(const QString &sectionName)
    : ChatModelItem{Type::SectionSeparator}
    , sectionName_{sectionName}
{

}

QVariant SectionSeparator::dataImp(int role) const
{
    switch (role) {
    case Roles::SectionName: return sectionName_; break;
    }
    return QVariant{};
}
