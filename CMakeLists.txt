cmake_minimum_required(VERSION 3.10)

project(TCPServer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the path for the WS2_32.lib
set(WS2_32_LIB_PATH "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.22621.0/um/x64")

# Include directories for header files
include_directories(inc src)

# Debug message to show include directories
message(STATUS "Include directories: ${CMAKE_CURRENT_SOURCE_DIR}/inc; ${CMAKE_CURRENT_SOURCE_DIR}/src")

# Find the WS2_32 library
find_library(WS2_32_LIB NAMES ws2_32 PATHS ${WS2_32_LIB_PATH})

if(NOT WS2_32_LIB)
    message(FATAL_ERROR "WS2_32.lib not found.")
else()
    message(STATUS "Ws2_32.lib found at: ${WS2_32_LIB}")
endif()

# Set the source files
set(SOURCES 
    server.cpp
    src/http_tcp.cpp
)

# Add the executable
add_executable(TCPServer ${SOURCES})

# Link the WS2_32 library
target_link_libraries(TCPServer ${WS2_32_LIB})

# Set the output directory for the executable
set_target_properties(TCPServer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
