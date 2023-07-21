cmake_minimum_required(VERSION 3.15)
set(APP_NAME AbdugramDesktop)
project(${APP_NAME} VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Network)

set(HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SQL_SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/../AbdugramLibs/sql_client/sql)
set(SQL_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/.sql)

set(HEADERS
    ${HEADERS_DIR}/net/clientmessagevisitor.h
    ${HEADERS_DIR}/net/networkhandler.h
    ${HEADERS_DIR}/sectimer.h
    ${HEADERS_DIR}/application.h
    ${HEADERS_DIR}/settings.h
    ${HEADERS_DIR}/ui/welcomebutton.h
    ${HEADERS_DIR}/ui/chatheader.h
    ${HEADERS_DIR}/ui/conversationside.h
    ${HEADERS_DIR}/ui/fieldlineedit.h
    ${HEADERS_DIR}/ui/headerlabel.h
    ${HEADERS_DIR}/ui/hellopage.h
    ${HEADERS_DIR}/ui/imagebutton.h
    ${HEADERS_DIR}/ui/lineedit.h
    ${HEADERS_DIR}/ui/loginpage.h
    ${HEADERS_DIR}/ui/mainlabel.h
    ${HEADERS_DIR}/ui/mainpage.h
    ${HEADERS_DIR}/ui/mainwindow.h
    ${HEADERS_DIR}/ui/messagetextedit.h
    ${HEADERS_DIR}/ui/mv/chatmodelitem.h
    ${HEADERS_DIR}/ui/mv/chatitem.h
    ${HEADERS_DIR}/ui/mv/chatlistdelegate.h
    ${HEADERS_DIR}/ui/mv/chatlistmodel.h
    ${HEADERS_DIR}/ui/mv/chatlistview.h
    ${HEADERS_DIR}/ui/mv/founduseritem.h
    ${HEADERS_DIR}/ui/mv/lineseparatoritem.h
    ${HEADERS_DIR}/ui/mv/messagemodelitem.h
    ${HEADERS_DIR}/ui/mv/messageitem.h
    ${HEADERS_DIR}/ui/mv/dateseparatoritem.h
    ${HEADERS_DIR}/ui/mv/messagelistdelegate.h
    ${HEADERS_DIR}/ui/mv/messagelistmodel.h
    ${HEADERS_DIR}/ui/mv/messagelistview.h
    ${HEADERS_DIR}/ui/passwordlineedit.h
    ${HEADERS_DIR}/ui/phonelineedit.h
    ${HEADERS_DIR}/ui/problemwidget.h
    ${HEADERS_DIR}/ui/regexes.h
    ${HEADERS_DIR}/ui/registrationpage.h
    ${HEADERS_DIR}/ui/rippleanimation.h
    ${HEADERS_DIR}/ui/searchlineedit.h
    ${HEADERS_DIR}/ui/secondarylabel.h
    ${HEADERS_DIR}/ui/sidepanel.h
    ${HEADERS_DIR}/ui/stackedwidget.h
    ${HEADERS_DIR}/ui/textedit.h
    ${HEADERS_DIR}/ui/sidemenu.h
    ${HEADERS_DIR}/ui/sidemenubutton.h
    ${HEADERS_DIR}/ui/colorrepository.h
)

set(SOURCES
    ${SOURCES_DIR}/main.cpp
    ${SOURCES_DIR}/net/clientmessagevisitor.cpp
    ${SOURCES_DIR}/net/networkhandler.cpp
    ${SOURCES_DIR}/sectimer.cpp
    ${SOURCES_DIR}/application.cpp
    ${SOURCES_DIR}/settings.cpp
    ${SOURCES_DIR}/ui/welcomebutton.cpp
    ${SOURCES_DIR}/ui/chatheader.cpp
    ${SOURCES_DIR}/ui/conversationside.cpp
    ${SOURCES_DIR}/ui/fieldlineedit.cpp
    ${SOURCES_DIR}/ui/headerlabel.cpp
    ${SOURCES_DIR}/ui/hellopage.cpp
    ${SOURCES_DIR}/ui/imagebutton.cpp
    ${SOURCES_DIR}/ui/lineedit.cpp
    ${SOURCES_DIR}/ui/loginpage.cpp
    ${SOURCES_DIR}/ui/mainlabel.cpp
    ${SOURCES_DIR}/ui/mainpage.cpp
    ${SOURCES_DIR}/ui/mainwindow.cpp
    ${SOURCES_DIR}/ui/messagetextedit.cpp
    ${SOURCES_DIR}/ui/mv/chatmodelitem.cpp
    ${SOURCES_DIR}/ui/mv/chatitem.cpp
    ${SOURCES_DIR}/ui/mv/chatlistdelegate.cpp
    ${SOURCES_DIR}/ui/mv/chatlistmodel.cpp
    ${SOURCES_DIR}/ui/mv/chatlistview.cpp
    ${SOURCES_DIR}/ui/mv/founduseritem.cpp
    ${SOURCES_DIR}/ui/mv/lineseparatoritem.cpp
    ${SOURCES_DIR}/ui/mv/messagemodelitem.cpp
    ${SOURCES_DIR}/ui/mv/messageitem.cpp
    ${SOURCES_DIR}/ui/mv/dateseparatoritem.cpp
    ${SOURCES_DIR}/ui/mv/messagelistdelegate.cpp
    ${SOURCES_DIR}/ui/mv/messagelistmodel.cpp
    ${SOURCES_DIR}/ui/mv/messagelistview.cpp
    ${SOURCES_DIR}/ui/passwordlineedit.cpp
    ${SOURCES_DIR}/ui/phonelineedit.cpp
    ${SOURCES_DIR}/ui/problemwidget.cpp
    ${SOURCES_DIR}/ui/regexes.cpp
    ${SOURCES_DIR}/ui/registrationpage.cpp
    ${SOURCES_DIR}/ui/rippleanimation.cpp
    ${SOURCES_DIR}/ui/searchlineedit.cpp
    ${SOURCES_DIR}/ui/secondarylabel.cpp
    ${SOURCES_DIR}/ui/sidepanel.cpp
    ${SOURCES_DIR}/ui/stackedwidget.cpp
    ${SOURCES_DIR}/ui/textedit.cpp
    ${SOURCES_DIR}/ui/sidemenu.cpp
    ${SOURCES_DIR}/ui/sidemenubutton.cpp
    ${SOURCES_DIR}/ui/colorrepository.cpp
)

set(RESOURCES
    rcs/fonts.qrc
    rcs/images.qrc
    rcs/qss.qrc
)

add_executable(${APP_NAME} ${HEADERS} ${SOURCES} ${RESOURCES})

target_sources(${APP_NAME} PRIVATE ${HEADERS} ${SOURCES})

target_include_directories(${APP_NAME} PRIVATE ${HEADERS_DIR})

target_link_libraries(${APP_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Network
)

target_link_libraries(${APP_NAME} PRIVATE
    logger
    sql_client
    net_common
)

file (GLOB SQL_FILES ${SQL_SOURCE_DIR}/*)
file(COPY ${SQL_FILES} DESTINATION ${SQL_BINARY_DIR})
