# TCP Server in C++

This project implements a simple TCP server in C++ that listens for incoming client connections and serves HTML web pages in response. The server demonstrates foundational socket programming concepts and provides a basic framework for developing networked applications.

## Features
- Handles multiple client connections
- Serves static HTML content

## Installation
1. Without CMake, in the folder containing `server.cpp`, use the command:
    ```bash
    cl /EHsc server.cpp src/http_tcp.cpp /I inc ws2_32.lib
    ```
2. With CMake:
    - Create a build directory:
      ```bash
      mkdir build
      cd build
      ```
    - Run CMake to configure the project:
      ```bash
      cmake ..
      ```
    - Compile the project:
      ```bash
      cmake --build .
      ```

## Usage
Connect to the server using a web browser and default port number is 8080

