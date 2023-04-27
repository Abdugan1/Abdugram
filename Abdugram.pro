TEMPLATE = subdirs

SUBDIRS += \
    AbdugramClient \
    AbdugramServer \
    DataStructures \
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
DataStructures.file = DataStructures/DataStructures.pro

AbdugramClient.depends += NetCommon
AbdugramClient.depends += SqlClient

AbdugramServer.depends += SqlServer

SqlServer.depends += DataStructures
NetCommon.depends += DataStructures

OTHER_FILES += \
    Functions.pri \
    AppDirsConfig.pri \
    LibDirsConfig.pri
