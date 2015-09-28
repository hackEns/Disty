#include "UDPServer.hpp"

#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

namespace udpserver {
    UDPServer::UDPServer(const int port)
        : port_(port), sock_(0)
    {
        // Create a socket
        sock_ = socket(AF_INET, SOCK_DGRAM, 0);

        if (-1 == sock_) {
            std::cerr << "[ERROR] Unable to create a socket." << std::endl;
        }

        // Listen on any interface on specified port
        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = INADDR_ANY;
        server_addr.sin_port = htons(port);

        // Bind socket
        int ret = bind(sock_, (struct sockaddr *) &server_addr, sizeof(struct sockaddr));
        if (ret == -1) {
            std::cerr << "[ERROR] Unable to bind." << std::endl;
        } else {
            std::cout << "[INFO] Bind successful." << std::endl;
        }
    }


    UDPServer::~UDPServer(void) {
        // Close the socket
        close(sock_);
    }


    std::string UDPServer::poll(void) {
        // Receive data
        char buffer[BUFFER_LENGTH] = {'\0'};
        int count = recvfrom(sock_, &buffer, BUFFER_LENGTH, 0, NULL, 0);

        // Handle it
        if (count == -1) {
            return "";
        } else {
            return std::string(buffer);
        }
    }
}
