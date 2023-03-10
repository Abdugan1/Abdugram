TEMPLATE = subdirs

SUBDIRS += \
    AbdugramClient \
    AbdugramServer \
    Logger \
    NetCommon \
    NetServer \
    SqlClient \
    SqlCommon \
    SqlServer

AbdugramClient.file = AbdugramClient/AbdugramClient.pro
AbdugramServer.file = AbdugramServer/AbdugramServer.pro
SqlClient.file      = SqlClient/SqlClient.pro
SqlCommon.file      = SqlCommon/SqlCommon.pro
SqlServer.file      = SqlServer/SqlServer.pro
NetCommon.file      = NetCommon/NetCommon.pro
NetServer.file      = NetServer/NetServer.pro

AbdugramClient.depends += NetCommon
AbdugramClient.depends += SqlClient

AbdugramServer.depends += NetServer
AbdugramServer.depends += SqlServer

NetServer.depends += NetCommon

OTHER_FILES += \
    Functions.pri \
    AppDirsConfig.pri \
    LibDirsConfig.pri
