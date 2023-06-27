#ifndef SQLCLIENT_GLOBAL_H
#define SQLCLIENT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SQLCLIENT_LIBRARY)
#  define SQLCLIENT_EXPORT Q_DECL_EXPORT
#else
#  define SQLCLIENT_EXPORT Q_DECL_IMPORT
#endif

#endif // SQLCLIENT_GLOBAL_H
