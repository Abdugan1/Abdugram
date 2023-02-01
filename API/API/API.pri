QT -= gui
QT += core network

TEMPLATE = lib
CONFIG += c++17

include($$PWD/../../LibDirsConfig.pri)
include($$PWD/../../Functions.pri)

INCLUDEPATH += $$PWD/src

SOURCES += \
    $$PWD/src/consts.cpp \
    $$PWD/src/fields.cpp \
    $$PWD/src/message.cpp \
    $$PWD/src/tcpsession.cpp \
    $$PWD/src/test.cpp \
    $$PWD/src/user.cpp

HEADERS += \
    $$PWD/src/consts.h \
    $$PWD/src/fields.h \
    $$PWD/src/API_global.h \
    $$PWD/src/message.h \
    $$PWD/src/tcpsession.h \
    $$PWD/src/test.h \
    $$PWD/src/user.h

copyFiles($$PWD/src/*.h, $$OUT_PWD/$$TARGET/include/$$TARGET)
