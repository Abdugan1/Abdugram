cmake_minimum_required(VERSION 3.15)
set(APP_NAME AbdugramServer)
project(${APP_NAME})

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Curses REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Sql Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Sql Network)

set(HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SQL_SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/../AbdugramLibs/sql_server/sql)
set(SQL_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/.sql)

set(HEADERS
    ${HEADERS_DIR}/net/networkhandler.h
    ${HEADERS_DIR}/net/server.h
    ${HEADERS_DIR}/net/servermessagevisitor.h
    ${HEADERS_DIR}/net/threadpool.h
    ${HEADERS_DIR}/net/session.h
    ${HEADERS_DIR}/ui/cursedwindow.h
    ${HEADERS_DIR}/ui/logsviewpage.h
    ${HEADERS_DIR}/ui/mainmenupage.h
    ${HEADERS_DIR}/ui/serverwindow.h
    ${HEADERS_DIR}/ui/titledwindow.h
    ${HEADERS_DIR}/serverlogger.h
)

set(SOURCES
    ${SOURCES_DIR}/main.cpp
    ${SOURCES_DIR}/net/networkhandler.cpp
    ${SOURCES_DIR}/net/server.cpp
    ${SOURCES_DIR}/net/servermessagevisitor.cpp
    ${SOURCES_DIR}/net/threadpool.cpp
    ${SOURCES_DIR}/net/session.cpp
    ${SOURCES_DIR}/ui/cursedwindow.cpp
    ${SOURCES_DIR}/ui/logsviewpage.cpp
    ${SOURCES_DIR}/ui/mainmenupage.cpp
    ${SOURCES_DIR}/ui/serverwindow.cpp
    ${SOURCES_DIR}/ui/titledwindow.cpp
    ${SOURCES_DIR}/serverlogger.cpp
)

add_executable(${APP_NAME} ${SOURCES})

target_sources(${APP_NAME} PRIVATE ${HEADERS} ${SOURCES})

target_include_directories(${APP_NAME} PRIVATE ${HEADERS_DIR})

target_link_libraries(${APP_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Network
)

# ncurses
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(${APP_NAME} PRIVATE
    ${CURSES_LIBRARIES}
    menu
)


target_link_libraries(${APP_NAME} PRIVATE
    logger
    sql_server
    net_common
)

file (GLOB SQL_FILES ${SQL_SOURCE_DIR}/*)
file(COPY ${SQL_FILES} DESTINATION ${SQL_BINARY_DIR})
