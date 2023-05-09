QT += core gui widgets sql network

CONFIG += c++17

include($$PWD/../AppDirsConfig.pri)
include($$PWD/../Functions.pri)

# net library
INCLUDEPATH += $$PWD/../NetCommon/include
LIBS += -L$$OUT_PWD/../NetCommon/net_common/lib -lnet_common

# sql library
INCLUDEPATH += $$PWD/../SqlClient/include
LIBS += -L$$OUT_PWD/../SqlClient/sql_client/lib -lsql_client

INCLUDEPATH += $$PWD/../SqlCommon/include
LIBS += -L$$OUT_PWD/../SqlCommon/sql_common/lib -lsql_common

# logger library
INCLUDEPATH += $$PWD/../Logger/include
LIBS += -L$$OUT_PWD/../Logger/logger/lib -llogger

# self
INCLUDEPATH += $$PWD/src/

SOURCES += \
    src/main.cpp \
    src/net/clientmessagevisitor.cpp \
    src/net/networkhandler.cpp \
    src/sectimer.cpp \
    src/ui/button.cpp \
    src/ui/chatheader.cpp \
    src/ui/conversationside.cpp \
    src/ui/fieldlineedit.cpp \
    src/ui/headerlabel.cpp \
    src/ui/hellopage.cpp \
    src/ui/imagebutton.cpp \
    src/ui/lineedit.cpp \
    src/ui/loginpage.cpp \
    src/ui/mainlabel.cpp \
    src/ui/mainpage.cpp \
    src/ui/mainwindow.cpp \
    src/ui/messageside.cpp \
    src/ui/messagetextedit.cpp \
    src/ui/mv/chatitem.cpp \
    src/ui/mv/chatlistdelegate.cpp \
    src/ui/mv/chatlistmodel.cpp \
    src/ui/mv/chatlistview.cpp \
    src/ui/mv/messageitem.cpp \
    src/ui/mv/messagelistdelegate.cpp \
    src/ui/mv/messagelistmodel.cpp \
    src/ui/mv/messagelistview.cpp \
    src/ui/passwordlineedit.cpp \
    src/ui/phonelineedit.cpp \
    src/ui/problemwidget.cpp \
    src/ui/regexes.cpp \
    src/ui/registrationpage.cpp \
    src/ui/rippleanimation.cpp \
    src/ui/searchlineedit.cpp \
    src/ui/secondarylabel.cpp \
    src/ui/sidepanel.cpp \
    src/ui/stackedwidget.cpp \
    src/ui/textedit.cpp

HEADERS += \
    src/net/clientmessagevisitor.h \
    src/net/networkhandler.h \
    src/sectimer.h \
    src/ui/button.h \
    src/ui/chatheader.h \
    src/ui/conversationside.h \
    src/ui/fieldlineedit.h \
    src/ui/headerlabel.h \
    src/ui/hellopage.h \
    src/ui/imagebutton.h \
    src/ui/lineedit.h \
    src/ui/loginpage.h \
    src/ui/mainlabel.h \
    src/ui/mainpage.h \
    src/ui/mainwindow.h \
    src/ui/messageside.h \
    src/ui/messagetextedit.h \
    src/ui/mv/chatitem.h \
    src/ui/mv/chatlistdelegate.h \
    src/ui/mv/chatlistmodel.h \
    src/ui/mv/chatlistview.h \
    src/ui/mv/messageitem.h \
    src/ui/mv/messagelistdelegate.h \
    src/ui/mv/messagelistmodel.h \
    src/ui/mv/messagelistview.h \
    src/ui/passwordlineedit.h \
    src/ui/phonelineedit.h \
    src/ui/problemwidget.h \
    src/ui/regexes.h \
    src/ui/registrationpage.h \
    src/ui/rippleanimation.h \
    src/ui/searchlineedit.h \
    src/ui/secondarylabel.h \
    src/ui/sidepanel.h \
    src/ui/stackedwidget.h \
    src/ui/textedit.h

RESOURCES += \
    rcs/fonts.qrc \
    rcs/images.qrc \
    rcs/qss.qrc

OTHER_FILES += \
    $$DESTDIR/sql


# Copy *.sql files to build_dir/sql directory
LIB_SQL_FILES = $$OUT_PWD/../SqlClient/sql_client/sql/*
APP_SQL_DIR   = $$DESTDIR/.sql/

copyDir($$LIB_SQL_FILES, $$APP_SQL_DIR)
