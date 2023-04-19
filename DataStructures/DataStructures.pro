QT -= gui

TEMPLATE = lib
DEFINES += DATASTRUCTURES_LIBRARY
CONFIG += c++17
TARGET = data_structures

include($$PWD/../LibDirsConfig.pri)

INCLUDEPATH += ./include/data_structures/

HEADERS += \
    include/data_structures/DataStructures_global.h \
    include/data_structures/chat.h \
    include/data_structures/user.h

SOURCES += \
    include/data_structures/chat.cpp \
    src/user.cpp
