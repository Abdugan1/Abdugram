cmake_minimum_required(VERSION 3.15)
set(LIBRARY_NAME logger)
project(${LIBRARY_NAME} VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network)

set(HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/${LIBRARY_NAME})
set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(LIB_DIR ${CMAKE_CURRENT_BINARY_DIR}/lib)

set(HEADERS
    ${HEADERS_DIR}/Logger_global.h
    ${HEADERS_DIR}/logfile.h
    ${HEADERS_DIR}/logger.h
)

set(SOURCES
    ${SOURCES_DIR}/logfile.cpp
    ${SOURCES_DIR}/logger.cpp
)

add_library(${LIBRARY_NAME} SHARED ${SOURCES})

target_sources(${LIBRARY_NAME} PRIVATE ${HEADERS} ${SOURCES})

target_include_directories(${LIBRARY_NAME} INTERFACE ${INCLUDE_DIR})
target_include_directories(${LIBRARY_NAME} PRIVATE   ${HEADERS_DIR})

target_compile_definitions(${LIBRARY_NAME} PRIVATE LOGGER_LIBRARY)

target_link_libraries(${LIBRARY_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
)

set_target_properties(${LIBRARY_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${LIB_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${LIB_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${LIB_DIR}
)
