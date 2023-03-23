QT -= gui

TARGET = logger
TEMPLATE = lib
CONFIG += shared
DEFINES += LOGGER_LIBRARY

CONFIG += c++17

include($$PWD/../LibDirsConfig.pri)
include($$PWD/../Functions.pri)

INCLUDEPATH += $$PWD/include/logger

SOURCES += \
    src/logfile.cpp \
    src/logger.cpp

HEADERS += \
    include/logger/Logger_global.h \
    include/logger/logfile.h \
    include/logger/logger.h
