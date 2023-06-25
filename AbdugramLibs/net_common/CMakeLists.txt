cmake_minimum_required(VERSION 3.15)
set(LIBRARY_NAME net_common)
project(${LIBRARY_NAME} VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network)

set(HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR}/include)
set(LIB_DIR ${CMAKE_CURRENT_BINARY_DIR}/lib)

# List the source files
set(HEADERS
    ${HEADERS_DIR}/NetCommon_global.h
    ${HEADERS_DIR}/consts.h
    ${HEADERS_DIR}/datastream.h
    ${HEADERS_DIR}/fields.h
    ${HEADERS_DIR}/messages/abdumessage.h
    ${HEADERS_DIR}/messages/abdumessagefactory.h
    ${HEADERS_DIR}/messages/createchatmessage.h
    ${HEADERS_DIR}/messages/createchatresultmessage.h
    ${HEADERS_DIR}/messages/loginmessage.h
    ${HEADERS_DIR}/messages/loginstatusmessage.h
    ${HEADERS_DIR}/messages/messagesforwarddeclaration.h
    ${HEADERS_DIR}/messages/messagevisitor.h
    ${HEADERS_DIR}/messages/registermessage.h
    ${HEADERS_DIR}/messages/registerstatusmessage.h
    ${HEADERS_DIR}/messages/searchonservermessage.h
    ${HEADERS_DIR}/messages/searchusersresultmessage.h
    ${HEADERS_DIR}/messages/sendmessagemessage.h
    ${HEADERS_DIR}/messages/sendmessageresultmessage.h
    ${HEADERS_DIR}/messages/syncchatsreply.h
    ${HEADERS_DIR}/messages/syncchatsrequest.h
    ${HEADERS_DIR}/messages/syncmessagesreply.h
    ${HEADERS_DIR}/messages/syncmessagesrequest.h
    ${HEADERS_DIR}/messages/syncusersmessage.h
    ${HEADERS_DIR}/messages/syncusersreply.h
    ${HEADERS_DIR}/tcpsession.h
)
set(SOURCES
    ${SOURCES_DIR}/consts.cpp
    ${SOURCES_DIR}/datastream.cpp
    ${SOURCES_DIR}/fields.cpp
    ${SOURCES_DIR}/messages/abdumessage.cpp
    ${SOURCES_DIR}/messages/abdumessagefactory.cpp
    ${SOURCES_DIR}/messages/createchatmessage.cpp
    ${SOURCES_DIR}/messages/createchatresultmessage.cpp
    ${SOURCES_DIR}/messages/loginmessage.cpp
    ${SOURCES_DIR}/messages/loginstatusmessage.cpp
    ${SOURCES_DIR}/messages/registermessage.cpp
    ${SOURCES_DIR}/messages/registerstatusmessage.cpp
    ${SOURCES_DIR}/messages/searchonservermessage.cpp
    ${SOURCES_DIR}/messages/searchusersresultmessage.cpp
    ${SOURCES_DIR}/messages/sendmessagemessage.cpp
    ${SOURCES_DIR}/messages/sendmessageresultmessage.cpp
    ${SOURCES_DIR}/messages/syncchatsreply.cpp
    ${SOURCES_DIR}/messages/syncchatsrequest.cpp
    ${SOURCES_DIR}/messages/syncmessagesreply.cpp
    ${SOURCES_DIR}/messages/syncmessagesrequest.cpp
    ${SOURCES_DIR}/messages/syncusersmessage.cpp
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

file(COPY ${HEADERS_DIR}/ DESTINATION ${INCLUDE_DIR}/${LIBRARY_NAME})
