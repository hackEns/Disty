#include "Robot.hpp"

#include <csignal>
#include <ctime>
#include <iostream>
#include <vector>

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
       // Init the camera holder
       camera_holder_.setPosition(100);

       sleep(1);
       camera_holder_.writeZeroSoftPWM();

       // Prevent the robot from moving
       stop();
    }

    Robot::~Robot(void)
    {
        // Stop the robot when destroying the Robot object
        stop();
    }

    void Robot::move(float speed) {
        speed = utilities::clamp(speed, -constants::MAX_SPEED, constants::MAX_SPEED);
        left_wheel_.setSpeed(speed * constants::LEFT_WHEEL_REDUCTION_FACTOR);
        right_wheel_.setSpeed(-speed * constants::RIGHT_WHEEL_REDUCTION_FACTOR);
    }

    void Robot::stop(void) {
        left_wheel_.setSpeed(0.0F);
        right_wheel_.setSpeed(0.0F);
        camera_holder_.writeZeroSoftPWM();
    }

    void Robot::lookAt(int angle) {
        angle = utilities::clamp(angle, constants::CAMERA_HOLDER_LOW_STOP, constants::CAMERA_HOLDER_HIGH_STOP);
        camera_holder_.setPosition(angle);
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
            std::vector<std::string> command_argv = utilities::split(command, ' ');
            std::cout << "[INFO] RECV successful, client says:" << command << std::endl;

            if ("FORWARD" == command_argv[0]) {
                if (command_argv.size() == 1) {
                    // No extra argument
                    move(1.0F);  // Speed is truncated to MAX_SPEED in move method
                } else {
                    // Extra argument speed is provided
                    move(std::stof(command_argv[1]));
                }
            } else if ("BACKWARD" == command_argv[0]) {
                if (command_argv.size() == 1) {
                    // No extra argument
                    move(-1.0F);  // Speed is truncated to MAX_SPEED in move method
                } else {
                    // Extra argument speed is provided
                    move(std::stof(command_argv[1]));
                }
            } else if ("STOP" == command_argv[0]) {
                stop();
            } else if ("LOOK" == command_argv[0]) {
                if ("UP" == command_argv[1]) {
                    lookAt(camera_holder_.getPosition() + 10);
                }
                else if ("DOWN" == command_argv[1]) {
                    lookAt(camera_holder_.getPosition() - 10);
                }
                else if ("AT" == command_argv[1]) {
                    if (command_argv.size() > 2) {
                        lookAt(std::stoi(command_argv[2]));
                    } else {
                        // Invalid command, do nothing
                    }
                } else {
                    // Invalid command, do nothing
                }
            } else if ("KILL" == command_argv[0]) {
                running = false;
            }
        }
    }
}
