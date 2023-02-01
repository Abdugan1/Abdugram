#ifndef API_SQL_GLOBAL_H
#define API_SQL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(API_SQL_CLIENT_LIBRARY) || defined(API_SQL_SERVER_LIBRARY)
#  define API_SQL_EXPORT Q_DECL_EXPORT
#else
#  define API_SQL_EXPORT Q_DECL_IMPORT
#endif

#endif // API_SQL_GLOBAL_H

