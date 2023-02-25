QT -= gui
QT += core network

TEMPLATE = lib
CONFIG += c++17

include($$PWD/../../LibDirsConfig.pri)
include($$PWD/../../Functions.pri)

INCLUDEPATH += $$PWD/src

SOURCES += \
    $$PWD/src/messages/abdumessage.cpp \
    $$PWD/src/consts.cpp \
    $$PWD/src/datastream.cpp \
    $$PWD/src/fields.cpp \
    $$PWD/src/message.cpp \
    $$PWD/src/messages/abdumessagefactory.cpp \
    $$PWD/src/messages/loginmessage.cpp \
    $$PWD/src/messages/loginstatusmessage.cpp \
    $$PWD/src/messages/registermessage.cpp \
    $$PWD/src/messages/registerstatusmessage.cpp \
    $$PWD/src/tcpsession.cpp \
    $$PWD/src/user.cpp

HEADERS += \
    $$PWD/src/messages/abdumessage.h \
    $$PWD/src/consts.h \
    $$PWD/src/datastream.h \
    $$PWD/src/fields.h \
    $$PWD/src/API_global.h \
    $$PWD/src/message.h \
    $$PWD/src/messages/abdumessagefactory.h \
    $$PWD/src/messages/loginmessage.h \
    $$PWD/src/messages/loginstatusmessage.h \
    $$PWD/src/messages/registermessage.h \
    $$PWD/src/messages/registerstatusmessage.h \
    $$PWD/src/tcpsession.h \
    $$PWD/src/user.h

contains(DEFINES, API_SERVER_LIBRARY) {
    SOURCES += \
        $$PWD/src/server.cpp \
        $$PWD/src/threadpool.cpp

    HEADERS += \
        $$PWD/src/server.h \
        $$PWD/src/threadpool.h
}

copyFiles($$PWD/src/*.h, $$OUT_PWD/$$TARGET/include/$$TARGET)
copyDir($$PWD/src/messages, $$OUT_PWD/$$TARGET/include/$$TARGET)
