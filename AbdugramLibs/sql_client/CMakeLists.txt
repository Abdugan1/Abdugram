cmake_minimum_required(VERSION 3.15)
set(LIBRARY_NAME sql_client)
project(${LIBRARY_NAME} VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Sql)

set(HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/${LIBRARY_NAME})
set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(LIB_DIR ${CMAKE_CURRENT_BINARY_DIR}/lib)

set(SQL_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/sql)
set(SQL_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/)

# List the source files
set(HEADERS
    ${HEADERS_DIR}/SqlClient_global.h
    ${HEADERS_DIR}/chatstable.h
    ${HEADERS_DIR}/chatuserstable.h
    ${HEADERS_DIR}/databaseclient.h
    ${HEADERS_DIR}/messagestable.h
    ${HEADERS_DIR}/userstable.h
)

set(SOURCES
    ${SOURCES_DIR}/chatstable.cpp
    ${SOURCES_DIR}/chatuserstable.cpp
    ${SOURCES_DIR}/databaseclient.cpp
    ${SOURCES_DIR}/messagestable.cpp
    ${SOURCES_DIR}/userstable.cpp
)

add_library(${LIBRARY_NAME} SHARED ${SOURCES})

target_sources(${LIBRARY_NAME} PRIVATE ${HEADERS} ${SOURCES})

target_include_directories(${LIBRARY_NAME} INTERFACE ${INCLUDE_DIR})
target_include_directories(${LIBRARY_NAME} PRIVATE   ${HEADERS_DIR})

target_compile_definitions(${LIBRARY_NAME} PRIVATE SQLCLIENT_LIBRARY)

target_link_libraries(${LIBRARY_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Sql
)

target_link_libraries(${LIBRARY_NAME} PUBLIC sql_common)

set_target_properties(${LIBRARY_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${LIB_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${LIB_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${LIB_DIR}
)

file(COPY ${SQL_SOURCE_DIR} DESTINATION ${SQL_BINARY_DIR})
