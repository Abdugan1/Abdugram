QT -= gui
QT += sql network

QTPLUGIN += QSQLMYSQL

CONFIG += c++17 console
CONFIG -= app_bundle

include($$PWD/../AppDirsConfig.pri)
include($$PWD/../Functions.pri)

# ncurses libraries
LIBS += -lmenu -lncurses

# net library
INCLUDEPATH += $$PWD/../NetCommon/include
LIBS += -L$$OUT_PWD/../NetCommon/net_common/lib -lnet_common

INCLUDEPATH += $$PWD/../NetServer/include
LIBS += -L$$OUT_PWD/../NetServer/net_server/lib -lnet_server

# sql library
INCLUDEPATH += $$PWD/../SqlServer/include
LIBS += -L$$OUT_PWD/../SqlServer/sql_server/lib -lsql_server

INCLUDEPATH += $$PWD/../SqlCommon/include
LIBS += -L$$OUT_PWD/../SqlCommon/sql_common/lib -lsql_common

# logger library
INCLUDEPATH += $$OUT_PWD/../Logger/logger/include
LIBS += -L$$OUT_PWD/../Logger/logger/lib -llogger

SOURCES += \
        cursedwindow.cpp \
        logsviewpage.cpp \
        main.cpp \
        mainmenupage.cpp \
        serverlogger.cpp \
        serverwindow.cpp \
        titledwindow.cpp

HEADERS += \
    cursedwindow.h \
    logsviewpage.h \
    mainmenupage.h \
    serverlogger.h \
    serverwindow.h \
    titledwindow.h

# Copy *.sql files to build_dir/sql directory
LIB_SQL_FILES = $$OUT_PWD/../SqlServer/sql_server/sql/*
APP_SQL_DIR   = $$DESTDIR/.sql/

copyDir($$LIB_SQL_FILES, $$APP_SQL_DIR)
