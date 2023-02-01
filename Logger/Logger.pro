QT -= gui

TARGET = logger
TEMPLATE = lib
DEFINES += LOGGER_LIBRARY

CONFIG += c++17

include($$PWD/../LibDirsConfig.pri)
include($$PWD/../Functions.pri)

SOURCES += \
    src/logger.cpp

HEADERS += \
    src/Logger_global.h \
    src/logger.h

copyFiles($$PWD/src/*.h, $$OUT_PWD/$$TARGET/include/$$TARGET/)
