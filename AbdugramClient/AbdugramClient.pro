QT += core gui widgets sql network

CONFIG += c++17

include($$PWD/../AppDirsConfig.pri)
include($$PWD/../Functions.pri)

# api_client library
INCLUDEPATH += $$OUT_PWD/../API/API_Client/api_client/include
LIBS += -L$$OUT_PWD/../API/API_Client/api_client/lib -lapi_client

# api_sql_client library
INCLUDEPATH += $$OUT_PWD/../API_SQL/API_SQL_Client/api_sql_client/include
LIBS += -L$$OUT_PWD/../API_SQL/API_SQL_Client/api_sql_client/lib -lapi_sql_client

# logger library
INCLUDEPATH += $$OUT_PWD/../Logger/logger/include
LIBS += -L$$OUT_PWD/../Logger/logger/lib -llogger

SOURCES += \
    src/main.cpp \
    src/sectimer.cpp \
    src/ui/button.cpp \
    src/ui/headerlabel.cpp \
    src/ui/hellopage.cpp \
    src/ui/imagebutton.cpp \
    src/ui/lineedit.cpp \
    src/ui/mainlabel.cpp \
    src/ui/mainwindow.cpp \
    src/ui/problemwidget.cpp \
    src/ui/registrationpage.cpp \
    src/ui/rippleanimation.cpp \
    src/ui/secondarylabel.cpp \
    src/ui/stackedwidget.cpp

HEADERS += \
    src/sectimer.h \
    src/ui/button.h \
    src/ui/headerlabel.h \
    src/ui/hellopage.h \
    src/ui/imagebutton.h \
    src/ui/lineedit.h \
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
LIB_SQL_FILES = $$OUT_PWD/../API_SQL/API_SQL_Client/api_sql_client/sql/*
APP_SQL_DIR   = $$DESTDIR/.sql/

copyDir($$LIB_SQL_FILES, $$APP_SQL_DIR)
