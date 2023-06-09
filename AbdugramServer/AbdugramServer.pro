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

# sql library
INCLUDEPATH += $$PWD/../SqlServer/include
LIBS += -L$$OUT_PWD/../SqlServer/sql_server/lib -lsql_server

INCLUDEPATH += $$PWD/../SqlCommon/include
LIBS += -L$$OUT_PWD/../SqlCommon/sql_common/lib -lsql_common

# logger library
INCLUDEPATH += $$PWD/../Logger/include
LIBS += -L$$OUT_PWD/../Logger/logger/lib -llogger

SOURCES += \
    src/main.cpp \
    src/net/server.cpp \
    src/net/servermessagevisitor.cpp \
    src/net/session.cpp \
    src/net/threadpool.cpp \
    src/serverlogger.cpp \
    src/ui/cursedwindow.cpp \
    src/ui/logsviewpage.cpp \
    src/ui/mainmenupage.cpp \
    src/ui/serverwindow.cpp \
    src/ui/titledwindow.cpp

HEADERS += \
    src/net/server.h \
    src/net/servermessagevisitor.h \
    src/net/session.h \
    src/net/threadpool.h \
    src/serverlogger.h \
    src/ui/cursedwindow.h \
    src/ui/logsviewpage.h \
    src/ui/mainmenupage.h \
    src/ui/serverwindow.h \
    src/ui/titledwindow.h

# Copy *.sql files to build_dir/sql directory
LIB_SQL_FILES = $$OUT_PWD/../SqlServer/sql_server/sql/*
APP_SQL_DIR   = $$DESTDIR/.sql/

copyDir($$LIB_SQL_FILES, $$APP_SQL_DIR)
