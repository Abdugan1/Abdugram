#ifndef SECTIONSEPARATOR_H
#define SECTIONSEPARATOR_H

#include "chatmodelitem.h"

class SectionSeparator : public ChatModelItem
{
public:
    enum Roles {
        SectionName = ChatModelItem::Roles::UserRole + 1
    };

    explicit SectionSeparator(const QString &sectionName);

protected:
    QVariant dataImp(int role) const override;

private:
    QString sectionName_;
};

#endif // SECTIONSEPARATOR_H
