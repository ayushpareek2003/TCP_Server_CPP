# TCP Server in C++

This project implements a simple TCP server in C++ that listens for incoming client connections and serves HTML web pages in response. Built using the MSVC compiler, the server demonstrates foundational socket programming concepts and provides a basic framework for developing more complex networked applications. To run the server, compile the code with the Visual Studio Developer Command Prompt and execute the generated binary. 

## Features
- Handles multiple client connections
- Serves static HTML content

## Installation
1. Without CMake, folder containg server cpp use the command
    ```bash
   cl /EHsc server.cpp src/http_tcp.cpp /I inc ws2_32.lib
    ```

   

## Usage
Connect to the server using a web browser or a tool like `curl` to see the served webpage.
