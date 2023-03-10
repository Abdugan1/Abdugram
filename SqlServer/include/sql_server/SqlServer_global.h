#ifndef SQLSERVER_GLOBAL_H
#define SQLSERVER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SQLSERVER_LIBRARY)
#  define SQLSERVER_EXPORT Q_DECL_EXPORT
#else
#  define SQLSERVER_EXPORT Q_DECL_IMPORT
#endif

#endif // SQLSERVER_GLOBAL_H
