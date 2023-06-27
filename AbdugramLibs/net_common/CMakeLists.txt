cmake_minimum_required(VERSION 3.15)
set(LIBRARY_NAME net_common)
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

# List the source files
set(HEADERS
    ${HEADERS_DIR}/NetCommon_global.h
    ${HEADERS_DIR}/consts.h
    ${HEADERS_DIR}/datastream.h
    ${HEADERS_DIR}/fields.h
    ${HEADERS_DIR}/messages/abdumessage.h
    ${HEADERS_DIR}/messages/abdumessagefactory.h
    ${HEADERS_DIR}/messages/createchatrequest.h
    ${HEADERS_DIR}/messages/createchatreply.h
    ${HEADERS_DIR}/messages/loginrequest.h
    ${HEADERS_DIR}/messages/loginreply.h
    ${HEADERS_DIR}/messages/messagesforwarddeclaration.h
    ${HEADERS_DIR}/messages/messagevisitor.h
    ${HEADERS_DIR}/messages/registerrequest.h
    ${HEADERS_DIR}/messages/registerreply.h
    ${HEADERS_DIR}/messages/searchrequest.h
    ${HEADERS_DIR}/messages/searchusersreply.h
    ${HEADERS_DIR}/messages/sendmessagerequest.h
    ${HEADERS_DIR}/messages/sendmessagereply.h
    ${HEADERS_DIR}/messages/syncchatsreply.h
    ${HEADERS_DIR}/messages/syncchatsrequest.h
    ${HEADERS_DIR}/messages/syncmessagesreply.h
    ${HEADERS_DIR}/messages/syncmessagesrequest.h
    ${HEADERS_DIR}/messages/syncusersrequest.h
    ${HEADERS_DIR}/messages/syncusersreply.h
    ${HEADERS_DIR}/tcpsession.h
)

set(SOURCES
    ${SOURCES_DIR}/consts.cpp
    ${SOURCES_DIR}/datastream.cpp
    ${SOURCES_DIR}/fields.cpp
    ${SOURCES_DIR}/messages/abdumessage.cpp
    ${SOURCES_DIR}/messages/abdumessagefactory.cpp
    ${SOURCES_DIR}/messages/createchatrequest.cpp
    ${SOURCES_DIR}/messages/createchatreply.cpp
    ${SOURCES_DIR}/messages/loginrequest.cpp
    ${SOURCES_DIR}/messages/loginreply.cpp
    ${SOURCES_DIR}/messages/registerrequest.cpp
    ${SOURCES_DIR}/messages/registerreply.cpp
    ${SOURCES_DIR}/messages/searchrequest.cpp
    ${SOURCES_DIR}/messages/searchusersreply.cpp
    ${SOURCES_DIR}/messages/sendmessagerequest.cpp
    ${SOURCES_DIR}/messages/sendmessagereply.cpp
    ${SOURCES_DIR}/messages/syncchatsreply.cpp
    ${SOURCES_DIR}/messages/syncchatsrequest.cpp
    ${SOURCES_DIR}/messages/syncmessagesreply.cpp
    ${SOURCES_DIR}/messages/syncmessagesrequest.cpp
    ${SOURCES_DIR}/messages/syncusersrequest.cpp
    ${SOURCES_DIR}/messages/syncusersreply.cpp
    ${SOURCES_DIR}/tcpsession.cpp
)

add_library(${LIBRARY_NAME} SHARED ${HEADERS} ${SOURCES})

target_sources(${LIBRARY_NAME} PRIVATE ${HEADERS} ${SOURCES})

target_include_directories(${LIBRARY_NAME} INTERFACE ${INCLUDE_DIR})
target_include_directories(${LIBRARY_NAME} PRIVATE   ${HEADERS_DIR})

target_link_libraries(net_common PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
)

target_link_libraries(${LIBRARY_NAME} PRIVATE sql_common)

set_target_properties(${LIBRARY_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${LIB_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${LIB_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${LIB_DIR}
)
