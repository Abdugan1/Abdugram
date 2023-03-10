#ifndef NETCOMMON_GLOBAL_H
#define NETCOMMON_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(NETCOMMON_LIBRARY)
#  define NETCOMMON_EXPORT Q_DECL_EXPORT
#else
#  define NETCOMMON_EXPORT Q_DECL_IMPORT
#endif

#endif // NETCOMMON_GLOBAL_H
