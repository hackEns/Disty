#include "Robot.hpp"

#include <csignal>
#include <iostream>

#include "constants.hpp"
#include "utilities.hpp"


namespace robot {
    Robot::Robot(void)
        : left_wheel_(
                constants::LEFT_WHEEL_PIN,
                constants::CONTINUOUS_SERVO_STOP_VALUE,
                constants::CONTINUOUS_SERVO_FULL_FORWARD_VALUE,
                constants::LEFT_WHEEL_IS_HARD_PWM),
        right_wheel_(
                constants::RIGHT_WHEEL_PIN,
                constants::CONTINUOUS_SERVO_STOP_VALUE,
                constants::CONTINUOUS_SERVO_FULL_FORWARD_VALUE,
                constants::RIGHT_WHEEL_IS_HARD_PWM),
        camera_holder_(
                constants::CAMERA_HOLDER_PIN,
                constants::STANDARD_SERVO_MIN_VALUE,
                constants::STANDARD_SERVO_MAX_VALUE,
                constants::CAMERA_HOLDER_IS_HARD_PWM),
        server_(constants::LISTENING_PORT)
    {
        // Empty on purpose
    }

    Robot::~Robot(void)
    {
        // Stop the robot when destroying the Robot object
        stop();
    }

    void Robot::move(const float speed) {
        left_wheel_.setSpeed(speed);
        right_wheel_.setSpeed(speed);
    }

    void Robot::stop(void) {
        left_wheel_.setSpeed(0.0F);
        right_wheel_.setSpeed(0.0F);
    }

    void Robot::lookAt(void) {
        // TODO
    }

    void Robot::listen(void) {
        bool running = true;
        while (running) {
            std::string command = server_.poll();

            if (command == "") {
                std::cerr << "[ERROR] RECV error." << std::endl;
                return;
            }

            utilities::trim(command);
            std::cout << "[INFO] RECV successful, client says:" << command << std::endl;

            if ("FORWARD" == command) {
                move(1.0F);
            }
            else if ("BACKWARD" == command) {
                // TODO: Not working
                move(-1.0F);
            }
            else if ("STOP" == command) {
                stop();
            }
            else if ("KILL" == command) {
                running = false;
            }
        }
    }
}
