cmake_minimum_required(VERSION 3.15)
set(APP_NAME AbdugramDesktop)
project(${APP_NAME} VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#find Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql Network Multimedia StateMachine)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql Network Multimedia StateMachine)

#find FramelessHelper
find_package(FramelessHelper REQUIRED COMPONENTS Core Widgets)

set(HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SQL_SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/../AbdugramLibs/sql_client/sql)
set(SQL_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/.sql)

set(HEADERS
    ${HEADERS_DIR}/net/clientmessagevisitor.h
    ${HEADERS_DIR}/net/networkhandler.h

    ${HEADERS_DIR}/ui/components/welcomebutton.h
    ${HEADERS_DIR}/ui/components/chatheader.h
    ${HEADERS_DIR}/ui/components/conversationside.h
    ${HEADERS_DIR}/ui/components/fieldlineedit.h
    ${HEADERS_DIR}/ui/components/headerlabel.h
    ${HEADERS_DIR}/ui/components/iconbutton.h
    ${HEADERS_DIR}/ui/components/mainlabel.h
    ${HEADERS_DIR}/ui/components/titlebar.h
    ${HEADERS_DIR}/ui/components/messageeditside.h
    ${HEADERS_DIR}/ui/components/passwordlineedit.h
    ${HEADERS_DIR}/ui/components/phonelineedit.h
    ${HEADERS_DIR}/ui/components/problemwidget.h
    ${HEADERS_DIR}/ui/components/regexes.h
    ${HEADERS_DIR}/ui/components/searchlineedit.h
    ${HEADERS_DIR}/ui/components/secondarylabel.h
    ${HEADERS_DIR}/ui/components/chatlistside.h
    ${HEADERS_DIR}/ui/components/stackedwidget.h
    ${HEADERS_DIR}/ui/components/sidemenu.h
    ${HEADERS_DIR}/ui/components/button.h
    ${HEADERS_DIR}/ui/components/colorrepository.h
    ${HEADERS_DIR}/ui/components/scrollbar.h
    ${HEADERS_DIR}/ui/components/notificationmanager.h
    ${HEADERS_DIR}/ui/components/notification.h
    ${HEADERS_DIR}/ui/components/widget.h

    ${HEADERS_DIR}/ui/styles/style.h

    ${HEADERS_DIR}/ui/effects/rippleanimation.h

    ${HEADERS_DIR}/ui/mv/chatmodelitem.h
    ${HEADERS_DIR}/ui/mv/chatitem.h
    ${HEADERS_DIR}/ui/mv/chatlistdelegate.h
    ${HEADERS_DIR}/ui/mv/chatlistmodel.h
    ${HEADERS_DIR}/ui/mv/chatlistview.h
    ${HEADERS_DIR}/ui/mv/founduseritem.h
    ${HEADERS_DIR}/ui/mv/sectionseparator.h
    ${HEADERS_DIR}/ui/mv/messagemodelitem.h
    ${HEADERS_DIR}/ui/mv/messageitem.h
    ${HEADERS_DIR}/ui/mv/dateseparatoritem.h
    ${HEADERS_DIR}/ui/mv/messagelistdelegate.h
    ${HEADERS_DIR}/ui/mv/messagelistmodel.h
    ${HEADERS_DIR}/ui/mv/messagelistview.h

    ${HEADERS_DIR}/ui/pages/hellopage.h
    ${HEADERS_DIR}/ui/pages/loginpage.h
    ${HEADERS_DIR}/ui/pages/mainpage.h
    ${HEADERS_DIR}/ui/pages/registrationpage.h

    ${HEADERS_DIR}/ui/mainwindow.h

    ${HEADERS_DIR}/sectimer.h
    ${HEADERS_DIR}/application.h
    ${HEADERS_DIR}/settings.h
)

set(SOURCES
    ${SOURCES_DIR}/net/clientmessagevisitor.cpp
    ${SOURCES_DIR}/net/networkhandler.cpp

    ${SOURCES_DIR}/ui/components/welcomebutton.cpp
    ${SOURCES_DIR}/ui/components/chatheader.cpp
    ${SOURCES_DIR}/ui/components/conversationside.cpp
    ${SOURCES_DIR}/ui/components/fieldlineedit.cpp
    ${SOURCES_DIR}/ui/components/headerlabel.cpp
    ${SOURCES_DIR}/ui/components/iconbutton.cpp
    ${SOURCES_DIR}/ui/components/mainlabel.cpp
    ${SOURCES_DIR}/ui/components/titlebar.cpp
    ${SOURCES_DIR}/ui/components/messageeditside.cpp
    ${SOURCES_DIR}/ui/components/passwordlineedit.cpp
    ${SOURCES_DIR}/ui/components/phonelineedit.cpp
    ${SOURCES_DIR}/ui/components/problemwidget.cpp
    ${SOURCES_DIR}/ui/components/regexes.cpp
    ${SOURCES_DIR}/ui/components/searchlineedit.cpp
    ${SOURCES_DIR}/ui/components/secondarylabel.cpp
    ${SOURCES_DIR}/ui/components/chatlistside.cpp
    ${SOURCES_DIR}/ui/components/stackedwidget.cpp
    ${SOURCES_DIR}/ui/components/sidemenu.cpp
    ${SOURCES_DIR}/ui/components/button.cpp
    ${SOURCES_DIR}/ui/components/colorrepository.cpp
    ${SOURCES_DIR}/ui/components/scrollbar.cpp
    ${SOURCES_DIR}/ui/components/notificationmanager.cpp
    ${SOURCES_DIR}/ui/components/notification.cpp
    ${SOURCES_DIR}/ui/components/widget.cpp

    ${SOURCES_DIR}/ui/styles/style.cpp

    ${SOURCES_DIR}/ui/effects/rippleanimation.cpp

    ${SOURCES_DIR}/ui/mv/chatmodelitem.cpp
    ${SOURCES_DIR}/ui/mv/chatitem.cpp
    ${SOURCES_DIR}/ui/mv/chatlistdelegate.cpp
    ${SOURCES_DIR}/ui/mv/chatlistmodel.cpp
    ${SOURCES_DIR}/ui/mv/chatlistview.cpp
    ${SOURCES_DIR}/ui/mv/founduseritem.cpp
    ${SOURCES_DIR}/ui/mv/sectionseparator.cpp
    ${SOURCES_DIR}/ui/mv/messagemodelitem.cpp
    ${SOURCES_DIR}/ui/mv/messageitem.cpp
    ${SOURCES_DIR}/ui/mv/dateseparatoritem.cpp
    ${SOURCES_DIR}/ui/mv/messagelistdelegate.cpp
    ${SOURCES_DIR}/ui/mv/messagelistmodel.cpp
    ${SOURCES_DIR}/ui/mv/messagelistview.cpp

    ${SOURCES_DIR}/ui/pages/hellopage.cpp
    ${SOURCES_DIR}/ui/pages/loginpage.cpp
    ${SOURCES_DIR}/ui/pages/mainpage.cpp
    ${SOURCES_DIR}/ui/pages/registrationpage.cpp

    ${SOURCES_DIR}/ui/mainwindow.cpp

    ${SOURCES_DIR}/sectimer.cpp
    ${SOURCES_DIR}/application.cpp
    ${SOURCES_DIR}/settings.cpp
    ${SOURCES_DIR}/main.cpp
)

set(RESOURCES
    rcs/fonts.qrc
    rcs/images.qrc
    rcs/sounds.qrc
)

add_executable(${APP_NAME} ${SOURCES} ${RESOURCES})

target_sources(${APP_NAME} PRIVATE ${HEADERS} ${SOURCES})

target_include_directories(${APP_NAME} PRIVATE ${HEADERS_DIR})

target_link_libraries(${APP_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Multimedia
    Qt${QT_VERSION_MAJOR}::StateMachine
)

target_link_libraries(${APP_NAME} PRIVATE
    logger
    sql_client
    net_common
)

target_link_libraries(${APP_NAME} PRIVATE
    FramelessHelper::FramelessHelperCore
    FramelessHelper::FramelessHelperWidgets
)

file (GLOB SQL_FILES ${SQL_SOURCE_DIR}/*)
file(COPY ${SQL_FILES} DESTINATION ${SQL_BINARY_DIR})
