QT -= gui
QT += core sql

TEMPLATE = lib
DEFINES += SQLCOMMON_LIBRARY
CONFIG += c++17
TARGET = sql_common

include($$PWD/../LibDirsConfig.pri)
include($$PWD/../Functions.pri)

INCLUDEPATH += include/sql_common

SOURCES += \
    src/data_structures/chat.cpp \
    src/data_structures/user.cpp \
    src/database.cpp \
    src/functions.cpp

HEADERS += \
    include/sql_common/data_structures/chat.h \
    include/sql_common/data_structures/user.h \
    include/sql_common/database.h \
    include/sql_common/SqlCommon_global.h \
    include/sql_common/functions.h

