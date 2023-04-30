QT -= gui
QT += core sql

TEMPLATE = lib
DEFINES += SQLSERVER_LIBRARY
CONFIG += c++17
TARGET = sql_server

include($$PWD/../LibDirsConfig.pri)
include($$PWD/../Functions.pri)

INCLUDEPATH += include/sql_server
INCLUDEPATH += ../SqlCommon/include

SOURCES += \
    src/userstable.cpp \
    src/chatstable.cpp \
    src/databaseserver.cpp

HEADERS += \
    include/sql_server/SqlServer_global.h \
    include/sql_server/chatstable.h \
    include/sql_server/databaseserver.h \
    include/sql_server/userstable.h

DISTFILES += \
    sql/user_contacts/constraints.sql \
    sql/user_contacts/create.sql \
    sql/user_statuses/constraints.sql \
    sql/user_statuses/create.sql \
    sql/users/constraints.sql \
    sql/users/create.sql

SQL_IN_DIR  = $$PWD/sql/*
SQL_OUT_DIR = $$OUT_PWD/$$TARGET/sql/
copyDir($$SQL_IN_DIR, $$SQL_OUT_DIR)
