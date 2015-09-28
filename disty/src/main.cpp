#include <arpa/inet.h>
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <wiringPi.h>

#include "constants.hpp"
#include "Robot.hpp"


#include <softPwm.h>
void exitHandler(int signal) {
    // End exit as the client would do, sending "KILL" to local UDP server
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(constants::LISTENING_PORT);

    const char buffer[] = "KILL";
    sendto(
            sock,
            buffer,
            sizeof(buffer),
            0,
            (struct sockaddr *) &servaddr,
            sizeof(servaddr));
}


int main(void) {
    // Setup wiringPi with Broadcom pin numbering
    wiringPiSetupGpio();

    // Handle ^C signal
    std::signal(SIGINT, exitHandler);

    robot::Robot disty;

    // Poll commands
    disty.listen();

    return EXIT_SUCCESS;
}
