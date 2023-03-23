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
    src/sectimer.cpp \
    src/ui/button.cpp \
    src/ui/headerlabel.cpp \
    src/ui/hellopage.cpp \
    src/ui/imagebutton.cpp \
    src/ui/lineedit.cpp \
    src/ui/loginpage.cpp \
    src/ui/mainlabel.cpp \
    src/ui/mainwindow.cpp \
    src/ui/problemwidget.cpp \
    src/ui/registrationpage.cpp \
    src/ui/rippleanimation.cpp \
    src/ui/secondarylabel.cpp \
    src/ui/stackedwidget.cpp

HEADERS += \
    src/net/clientmessagevisitor.h \
    src/sectimer.h \
    src/ui/button.h \
    src/ui/headerlabel.h \
    src/ui/hellopage.h \
    src/ui/imagebutton.h \
    src/ui/lineedit.h \
    src/ui/loginpage.h \
    src/ui/mainlabel.h \
    src/ui/mainwindow.h \
    src/ui/problemwidget.h \
    src/ui/registrationpage.h \
    src/ui/rippleanimation.h \
    src/ui/secondarylabel.h \
    src/ui/stackedwidget.h

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
