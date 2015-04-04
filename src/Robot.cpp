#include "Robot.hpp"

#include <csignal>

#include "constants.hpp"


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
        server_(constants::LISTENING_PORT);
    {
        // Empty on purpose
    }

    void Robot::move(const float distance_forward, const float turn) {
        // TODO
    }

    void Robot::stop(void) {
        left_wheel_.setSpeed(0);
        right_wheel_.setSpeed(0);
    }

    void Robot::lookAt(void) {
        // TODO
    }

    void Robot::stopServer(void) {
        server_.stop();
    }

    void Robot::listen(void) {
        std::string command = server_.poll();

        if (command == "") {
            std::cerr << "[ERROR] RECV error." << std::endl;
            return;
        }

        std::cout << "[INFO] RECV successful, client says:" << command << std::endl;

        // TODO
        switch (command) {
            case "FORWARD":
                break;

            case "BACKWARD":
                break;

            case "STOP":
                stop();
                break;

            case "KILL":
                // Stop the server
                stopServer();
                // Raise SIGINT, catched by the main thread, to exit the loop in the main thread
                std::raise(SIGINT);
                break;
        }
    }
}
