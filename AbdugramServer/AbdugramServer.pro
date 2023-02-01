QT -= gui
QT += sql network

QTPLUGIN += QSQLMYSQL

CONFIG += c++17 console
CONFIG -= app_bundle

include($$PWD/../AppDirsConfig.pri)
include($$PWD/../Functions.pri)

# ncurses libraries
LIBS += -lmenu -lncurses

# api_server library
INCLUDEPATH += $$OUT_PWD/../API/API_Server/api_server/include
LIBS += -L$$OUT_PWD/../API/API_Server/api_server/lib -lapi_server

# api_sql_server library
INCLUDEPATH += $$OUT_PWD/../API_SQL/API_SQL_Server/api_sql_server/include
LIBS += -L$$OUT_PWD/../API_SQL/API_SQL_Server/api_sql_server/lib -lapi_sql_server

# logger library
INCLUDEPATH += $$OUT_PWD/../Logger/logger/include
LIBS += -L$$OUT_PWD/../Logger/logger/lib -llogger

SOURCES += \
        cursedwindow.cpp \
        main.cpp \
        mainmenupage.cpp \
        serverwindow.cpp \
        titledwindow.cpp

HEADERS += \
    cursedwindow.h \
    mainmenupage.h \
    serverwindow.h \
    titledwindow.h

# Copy *.sql files to build_dir/sql directory
LIB_SQL_FILES = $$OUT_PWD/../API_SQL/API_SQL_Server/api_sql_server/sql/*
APP_SQL_DIR   = $$DESTDIR/.sql/

copyDir($$LIB_SQL_FILES, $$APP_SQL_DIR)
