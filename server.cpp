#include "inc/http_tcp.hpp"

int main(){
    std::string path;
    std::cout<<"Welcome to TCP server By Ayush Pareek, 11/10/2024"<<std::endl;
    std::cout<<" "<<std::endl;
    std::cout<<"Enter path to your Html File"<<std::endl;
    std::cin>>path;

    http::TCPServer server=http::TCPServer("127.0.0.1",8080,path);
    std::cout<<"Server started"<<std::endl;
    server.startlisten();

    return 0;
}
