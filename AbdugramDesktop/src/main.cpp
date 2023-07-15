#include "application.h"

#include <net_common/messages/abdumessage.h>
#include <net_common/tcpsession.h>

#include <sql_client/databaseclient.h>

#include <logger/logger.h>

int main(int argc, char *argv[])
{
    qRegisterMetaType<AbduMessagePtr>("AbduMessagePtr");

    Application app(argc, argv);

    return app.exec();
}
