#include "fields.h"

#define FIELDNAME const QString

namespace fieldnames {

    namespace user {
        FIELDNAME Id        = "id";
        FIELDNAME CreatedAt = "created_at";
        FIELDNAME UpdatedAt = "updated_at";
        FIELDNAME DeletedAt = "deleted_at";
    }

}
