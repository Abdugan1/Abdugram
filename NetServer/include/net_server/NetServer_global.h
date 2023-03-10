#ifndef NETSERVER_GLOBAL_H
#define NETSERVER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(NETSERVER_LIBRARY)
#  define NETSERVER_EXPORT Q_DECL_EXPORT
#else
#  define NETSERVER_EXPORT Q_DECL_IMPORT
#endif

#endif // NETSERVER_GLOBAL_H
