#ifndef CHATMODELITEM_H
#define CHATMODELITEM_H

#include <QVariant>

class ChatModelItem
{
public:
    enum Roles {
        Type = Qt::UserRole + 1,

        UserRole
    };

    enum Type {
        Unknown = -1,
        ChatItem,
        FoundUserItem,
        SectionSeparator
    };

    explicit ChatModelItem(enum Type type);
    virtual ~ChatModelItem() = default;

    QVariant data(int role) const;

    enum Type type() const;

protected:
    virtual QVariant dataImp(int role) const = 0;


private:
    enum Type type_ = Type::Unknown;
};

#endif // CHATMODELITEM_H
