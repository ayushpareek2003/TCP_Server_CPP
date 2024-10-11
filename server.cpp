#include "inc/http_tcp.hpp"

int main(){
    http::TCPServer server=http::TCPServer("127.0.0.1",8080);
    std::cout<<"Server started"<<std::endl;
    server.startlisten();

    return 0;
}
