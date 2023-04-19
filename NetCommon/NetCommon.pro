QT -= gui
QT += core network

TEMPLATE = lib
DEFINES = NETCOMMON_LIBRARY
CONFIG += c++17
TARGET = net_common

include($$PWD/../LibDirsConfig.pri)
include($$PWD/../Functions.pri)

INCLUDEPATH += $$PWD/include/net_common

HEADERS += \
    include/net_common/NetCommon_global.h \
    include/net_common/consts.h \
    include/net_common/datastream.h \
    include/net_common/fields.h \
    include/net_common/messages/abdumessage.h \
    include/net_common/messages/abdumessagefactory.h \
    include/net_common/messages/loginmessage.h \
    include/net_common/messages/loginstatusmessage.h \
    include/net_common/messages/messagesforwarddeclaration.h \
    include/net_common/messages/messagevisitor.h \
    include/net_common/messages/registermessage.h \
    include/net_common/messages/registerstatusmessage.h \
    include/net_common/messages/syncchatsrequest.h \
    include/net_common/tcpsession.h \

SOURCES += \
    include/net_common/messages/syncchatsrequest.cpp \
    src/consts.cpp \
    src/datastream.cpp \
    src/fields.cpp \
    src/messages/abdumessage.cpp \
    src/messages/abdumessagefactory.cpp \
    src/messages/loginmessage.cpp \
    src/messages/loginstatusmessage.cpp \
    src/messages/registermessage.cpp \
    src/messages/registerstatusmessage.cpp \
    src/tcpsession.cpp



