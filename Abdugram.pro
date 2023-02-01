TEMPLATE = subdirs

SUBDIRS += \
    API_Client \
    API_SQL_Client \
    API_Server \
    API_SQL_Server \
    AbdugramClient \
    AbdugramServer \
    Logger

API_Client.file     = API/API_Client/API_Client.pro
API_SQL_Client.file = API_SQL/API_SQL_Client/API_SQL_Client.pro
API_Server.file     = API/API_Server/API_Server.pro
API_SQL_Server.file = API_SQL/API_SQL_Server/API_SQL_Server.pro
AbdugramClient.file = AbdugramClient/AbdugramClient.pro
AbdugramServer.file = AbdugramServer/AbdugramServer.pro

AbdugramClient.depends = API_Client
AbdugramClient.depends = API_SQL_Client

AbdugramServer.depends = API_Server
AbdugramServer.depends = API_SQL_Server

API_SQL_Client.depends = API_Client
API_SQL_Server.depends = API_Server

OTHER_FILES += \
    Functions.pri \
    AppDirsConfig.pri \
    LibDirsConfig.pri
