#ifndef INCLUDED_HTTP_TCP
#define INCLUDED_HTTP_TCP
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>
#include <stdlib.h>


namespace http{

    
    class TCPServer{
        public:
            TCPServer(std::string ip_address,int port,std::string filename);
            ~TCPServer();

            int startServer();
            void closeServer();
            void acceptConnection(SOCKET &new_socket);
            std::string buildResponse(std:: string &filename);
            void sendResponse();
            void startlisten();

            

        private:
            std::string m_ip_address;
            int m_port;
            SOCKET m_socket;
            SOCKET m_new_socket;
            long m_incomingMessage;
            struct sockaddr_in m_socketAddress;
            int m_socketAddress_len;
            std::string m_serverMessage;
            

            WSADATA m_wsaData;



    };

    
}

#endif