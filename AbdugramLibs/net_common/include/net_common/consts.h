#ifndef CONSTS_H
#define CONSTS_H

#include "NetCommon_global.h"

#include <QString>

#define CONST_STR NETCOMMON_EXPORT extern const QString
#define CONST_INT NETCOMMON_EXPORT extern const int

namespace consts {

namespace server {

    CONST_STR Address;
    CONST_INT Port;
};

};

#undef CONST_STR
#undef CONST_INT

#endif // CONSTS_H
