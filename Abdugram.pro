TEMPLATE = subdirs

SUBDIRS += \
    AbdugramClient \
    AbdugramServer \
    Logger \
    NetCommon \
    SqlClient \
    SqlCommon \
    SqlServer

AbdugramClient.file = AbdugramClient/AbdugramClient.pro
AbdugramServer.file = AbdugramServer/AbdugramServer.pro
SqlClient.file      = SqlClient/SqlClient.pro
SqlCommon.file      = SqlCommon/SqlCommon.pro
SqlServer.file      = SqlServer/SqlServer.pro
NetCommon.file      = NetCommon/NetCommon.pro

AbdugramClient.depends += NetCommon
AbdugramClient.depends += SqlClient

AbdugramServer.depends += SqlServer

SqlClient.depends += SqlCommon
SqlServer.depends += SqlCommon

OTHER_FILES += \
    Functions.pri \
    AppDirsConfig.pri \
    LibDirsConfig.pri
