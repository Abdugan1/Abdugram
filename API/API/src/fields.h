#ifndef FIELDS_H
#define FIELDS_H

#include <QString>

#define FIELDNAME extern const QString

namespace fieldnames {

    namespace user {
        FIELDNAME Id;
        FIELDNAME CreatedAt;
        FIELDNAME UpdatedAt;
        FIELDNAME DeletedAt;
    }

}

namespace fieldnums {

    namespace user {
        enum {
            Id,
            CreatedAt,
            UpdatedAt,
            DeletedAt,
        };
    }

}

#undef FIELDNAME

#endif // FIELDS_H
