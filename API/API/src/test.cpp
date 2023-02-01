#include "test.h"
#include <QDebug>

Test::Test()
{
#if defined(API_CLIENT_LIBRARY)
    qDebug() << "CLIENT macro is defined!";
#elif defined(API_SERVER_LIBRARY)
    qDebug() << "SERVER macro is defined!";
#else
    qDebug() << "NO macro :(";
#endif
}
