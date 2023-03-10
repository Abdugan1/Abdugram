QT -= gui
QT += core network

TEMPLATE = lib
DEFINES = NETSERVER_LIBRARY
CONFIG += c++17
TARGET = net_server

include($$PWD/../LibDirsConfig.pri)
include($$PWD/../Functions.pri)

INCLUDEPATH += $$PWD/../NetCommon/include/
LIBS += -L$$OUT_PWD/../NetCommon/net_common/lib -lnet_common

INCLUDEPATH += $$PWD/include/net_server

HEADERS += \
    include/net_server/NetServer_global.h \
    include/net_server/server.h \
    include/net_server/threadpool.h

SOURCES += \
    src/server.cpp \
    src/threadpool.cpp
