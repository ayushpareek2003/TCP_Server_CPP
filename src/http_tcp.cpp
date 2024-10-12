#include "http_tcp.hpp"
#include <iostream>
#include <sstream>
#include <fstream>


#define BUFFER_SIZE 30720




http::TCPServer::TCPServer(std::string ip_address,int port,std::string filename):m_ip_address(ip_address),
    m_port(port),m_socket(),m_new_socket(),m_incomingMessage(),m_socketAddress(),
    m_socketAddress_len(sizeof(m_socketAddress)),m_serverMessage(buildResponse(filename)){

    m_socketAddress.sin_family=AF_INET;
    m_socketAddress.sin_port=htons(port);
    m_socketAddress.sin_addr.s_addr=inet_addr(m_ip_address.c_str());

    if(startServer()!=0){
        std::ostringstream ss;
        ss<<"### Failed to start server with PORT: "<<ntohs(m_socketAddress.sin_port)<<" ###";   
    }


}

http::TCPServer::~TCPServer(){
    closeServer();
}

int http::TCPServer::startServer(){
    if(WSAStartup(MAKEWORD(2,0), &m_wsaData)!=0){
        
        std::cout<<"WSAStartup Failed::"<<std::endl;
        return 1;
        
    }

    m_socket=socket(AF_INET,SOCK_STREAM,0);

    if(m_socket<0){
        std::cout<<"Can't create socket"<<std::endl;
        return 1;
    }

    if(bind(m_socket,(sockaddr *)&m_socketAddress,m_socketAddress_len)<0){
        std::cout<<"Cannot Process the connecting Request"<<std::endl;
        return 1;
    }


    return 0;


}

void http::TCPServer::closeServer(){
    closesocket(m_socket);
    closesocket(m_new_socket);
    WSACleanup();
    exit(0);

}

void http::TCPServer::startlisten() {
    if (listen(m_socket, 20) < 0) {
        std::cout << "Failed to listen" << std::endl;
        return;
    }

    std::ostringstream ss;
    ss << "\n*** Listening on ADDRESS: " << inet_ntoa(m_socketAddress.sin_addr)
       << " PORT: " << ntohs(m_socketAddress.sin_port) << " ***\n\n";
    std::cout << ss.str() << std::endl;

    int bytesReceived;
    char buffer[BUFFER_SIZE] = {0};

    while (true) {
        std::cout << "Waiting for a new connection" << std::endl;

        m_new_socket = accept(m_socket, nullptr, nullptr);
        if (m_new_socket < 0) {
            std::cout << "Failed to accept connection" << std::endl;
            continue;
        }

        bytesReceived = recv(m_new_socket, buffer, BUFFER_SIZE, 0);

        if (bytesReceived == 0) {
            std::cout << "Connection closed by client" << std::endl;
        } else if (bytesReceived < 0) {
            std::cout << "Failed to receive data" << std::endl;
        } else {
            std::ostringstream ss;
            ss << "------ Received -------" << std::endl;
            std::cout << ss.str() << std::endl;

           
            sendResponse();
        }

        closesocket(m_new_socket);
    }
}

void http::TCPServer::acceptConnection(SOCKET &new_socket){
    new_socket=accept(m_socket,(sockaddr *)&m_socketAddress,&m_socketAddress_len);

    if(new_socket<0){
        std::ostringstream ss;
        ss << "Server failed to accept incoming connection from ADDRESS: " << inet_ntoa(m_socketAddress.sin_addr) << "; PORT: " << ntohs(m_socketAddress.sin_port);

        return ;        
    }

}

std::string http::TCPServer::buildResponse(std::string &filename){
   
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return ""; 
    }

  
    std::ostringstream fileContentStream;
    fileContentStream << file.rdbuf(); 
    std::string htmlfile = fileContentStream.str();

   
    file.close();

    
    std::ostringstream ss;
    ss << "HTTP/1.1 200 OK\n"
       << "Content-Type: text/html\n"
       << "Content-Length: " << htmlfile.size() << "\n\n"
       << htmlfile;

    return ss.str();




}

void http::TCPServer::sendResponse(){

    int bytesSent;
    long totalBytesSent=0;

    while(totalBytesSent!=m_serverMessage.size()){
        bytesSent=send(m_new_socket,m_serverMessage.c_str(),m_serverMessage.size(),0);

        if(bytesSent<0){
            break;
        }
        totalBytesSent+=bytesSent;
    }

    if(totalBytesSent==m_serverMessage.size()){
        std::cout<<"Sent Succesfully"<<std::endl;

    }
    else{
        std::cout<<"Some Error occured"<<std::endl;
    }

}

