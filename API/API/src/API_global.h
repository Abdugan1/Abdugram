#ifndef API_GLOBAL_H
#define API_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(API_LIBRARY) || defined(API_CLIENT_LIBRARY) || defined(API_SERVER_LIBRARY)
#  define API_EXPORT Q_DECL_EXPORT
#else
#  define API_EXPORT Q_DECL_IMPORT
#endif

#endif // API_GLOBAL_H
