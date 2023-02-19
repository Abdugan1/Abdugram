QT -= gui

TARGET = logger
TEMPLATE = lib
CONFIG += shared
DEFINES += LOGGER_LIBRARY

CONFIG += c++17

include($$PWD/../LibDirsConfig.pri)
include($$PWD/../Functions.pri)

INCLUDEPATH += $$PWD/src

SOURCES += \
    src/logfile.cpp \
    src/logger.cpp

HEADERS += \
    src/Logger_global.h \
    src/logfile.h \
    src/logger.h

copyFiles($$PWD/src/*.h, $$OUT_PWD/$$TARGET/include/$$TARGET/)
