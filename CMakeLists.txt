cmake_minimum_required(VERSION 3.10)

project(TCPServer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(WS2_32_LIB_PATH "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22621.0/um/x64")


include_directories(inc)


message(STATUS "Include directories: ${CMAKE_CURRENT_SOURCE_DIR}/inc; ${CMAKE_CURRENT_SOURCE_DIR}/src")


find_library(WS2_32_LIB NAMES ws2_32 PATHS ${WS2_32_LIB_PATH})

if(NOT WS2_32_LIB)
    message(FATAL_ERROR "WS2_32.lib not found.")
else()
    message(STATUS "Ws2_32.lib found at: ${WS2_32_LIB}")
endif()


set(SOURCES 
    server.cpp
    src/http_tcp.cpp
)


add_executable(TCPServer ${SOURCES})


target_link_libraries(TCPServer ${WS2_32_LIB})


set_target_properties(TCPServer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
