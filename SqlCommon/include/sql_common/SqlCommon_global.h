#ifndef SQLCOMMON_GLOBAL_H
#define SQLCOMMON_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SQLCOMMON_LIBRARY)
#  define SQLCOMMON_EXPORT Q_DECL_EXPORT
#else
#  define SQLCOMMON_EXPORT Q_DECL_IMPORT
#endif

#endif // SQLCOMMON_GLOBAL_H
