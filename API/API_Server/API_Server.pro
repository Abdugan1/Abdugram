DEFINES += API_SERVER_LIBRARY
TARGET = api_server

include(../API/API.pri)

INCLUDEPATH = $$PWD/../API/src

HEADERS += \
    server.h

SOURCES += \
    server.cpp
