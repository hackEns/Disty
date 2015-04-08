#include <csignal>
#include <unistd.h>
#include <wiringPi.h>

#include "Robot.hpp"

namespace {
    volatile std::atomic<bool> running;
}


void exitHandler(int signal) {
    running = false;
}


int main(void) {
    // Setup wiringPi
    wiringPiSetup();

    // Handle ^C signal
    running = true;
    std::signal(SIGINT, exitHandler);

    robot::Robot disty;

    while (running) {
        // Poll commands
        disty.listen();
    }

    return EXIT_SUCCESS;
}
