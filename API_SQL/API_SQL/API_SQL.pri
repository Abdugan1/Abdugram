QT -= gui
QT += core sql

TEMPLATE = lib
CONFIG += c++17

include($$PWD/../../LibDirsConfig.pri)
include($$PWD/../../Functions.pri)

SOURCES += \
    $$PWD/src/database.cpp

HEADERS += \
	$$PWD/src/API_SQL_global.h \
	$$PWD/src/database.h


# Copy *.h files to build_dir/include
copyFiles($$PWD/src/*.h, $$OUT_PWD/$$TARGET/include/$$TARGET/)


# Copy *.sql files to build_dir/sql directory
contains(DEFINES, API_SQL_CLIENT_LIBRARY) {
    SQL_IN_DIR  = $$PWD/sql/client/*
}
contains(DEFINES, API_SQL_SERVER_LIBRARY) {
    SQL_IN_DIR  = $$PWD/sql/server/*
}

SQL_OUT_DIR = $$OUT_PWD/$$TARGET/sql/

copyDir($$SQL_IN_DIR, $$SQL_OUT_DIR)
