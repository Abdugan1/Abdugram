cmake_minimum_required(VERSION 3.15)
set(LIBRARY_NAME sql_common)
project(${LIBRARY_NAME} VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Sql)

# Add the source files
set(HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/${LIBRARY_NAME})
set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(LIB_DIR ${CMAKE_CURRENT_BINARY_DIR}/lib)

set(HEADERS
    ${HEADERS_DIR}/data_structures/chat.h
    ${HEADERS_DIR}/data_structures/chatuser.h
    ${HEADERS_DIR}/data_structures/message.h
    ${HEADERS_DIR}/data_structures/user.h
    ${HEADERS_DIR}/SqlCommon_global.h
    ${HEADERS_DIR}/functions.h
)

set(SOURCES
    ${SOURCES_DIR}/data_structures/chat.cpp
    ${SOURCES_DIR}/data_structures/chatuser.cpp
    ${SOURCES_DIR}/data_structures/message.cpp
    ${SOURCES_DIR}/data_structures/user.cpp
    ${SOURCES_DIR}/functions.cpp
)

add_library(${LIBRARY_NAME} SHARED ${SOURCES})

target_sources(${LIBRARY_NAME} PRIVATE ${SOURCES} ${HEADERS})

target_link_libraries(${LIBRARY_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Sql
)

target_include_directories(${LIBRARY_NAME} INTERFACE ${INCLUDE_DIR})
target_include_directories(${LIBRARY_NAME} PRIVATE ${HEADERS_DIR})

# Set the output directories
set_target_properties(${LIBRARY_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${LIB_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${LIB_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${LIB_DIR}
)
