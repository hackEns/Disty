#include <csignal>
#include <cstdlib>
#include <wiringPi.h>

#include "Robot.hpp"

void exitHandler(int signal) {
    exit(EXIT_SUCCESS);
}


int main(void) {
    // Setup wiringPi
    wiringPiSetup();

    // Handle ^C signal
    std::signal(SIGINT, exitHandler);

    robot::Robot disty;

    while (true) {
        // Poll commands
        disty.listen();
    }

    return EXIT_SUCCESS;
}
