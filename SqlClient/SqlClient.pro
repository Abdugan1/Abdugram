QT -= gui
QT += core sql

TEMPLATE = lib
DEFINES += SQLCLIENT_LIBRARY
CONFIG += c++17
TARGET = sql_client

include($$PWD/../LibDirsConfig.pri)
include($$PWD/../Functions.pri)

INCLUDEPATH += include/sql_client
INCLUDEPATH += ../SqlCommon/include

SOURCES += \
    src/chatstable.cpp \
    src/chatuserstable.cpp \
    src/databaseclient.cpp \
    src/userstable.cpp

HEADERS += \
    include/sql_client/SqlClient_global.h \
    include/sql_client/chatstable.h \
    include/sql_client/chatuserstable.h \
    include/sql_client/databaseclient.h \
    include/sql_client/userstable.h

DISTFILES += \
    sql/deleted_messages/create.sql \
    sql/messages/create.sql \
    sql/user_contacts/create.sql \
    sql/user_statuses/create.sql \
    sql/users/create.sql \
    sql/users/create.sql.save

# Copy *.sql files to build_dir/sql directory
SQL_IN_DIR  = $$PWD/sql/*
SQL_OUT_DIR = $$OUT_PWD/$$TARGET/sql/
copyDir($$SQL_IN_DIR, $$SQL_OUT_DIR)
