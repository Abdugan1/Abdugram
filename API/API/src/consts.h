#ifndef CONSTS_H
#define CONSTS_H

#include <QString>

#define CONST_STR extern const QString
#define CONST_INT extern const int

namespace consts {

namespace server {

    CONST_STR Address;
    CONST_INT Port;
};

};

#undef CONST_STR
#undef CONST_INT

#endif // CONSTS_H
