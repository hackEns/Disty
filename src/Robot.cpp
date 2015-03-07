#include "Robot.hpp"
namespace robot {
    Robot::Robot(void) {
        left_wheel_(
                Config("pins", "LEFT_WHEEL_PIN"),
                Config("constants", "CONTINUOUS_SERVO_STOP_VALUE")
                Config("constants", "CONTINUOUS_SERVO_FULL_FORWARD_VALUE")
                );
        right_wheel_(
                Config("pins", "RIGHT_WHEEL_PIN"),
                Config("constants", "CONTINUOUS_SERVO_STOP_VALUE")
                Config("constants", "CONTINUOUS_SERVO_FULL_FORWARD_VALUE")
                );
        camera_holder_(
                Config("pins", "CAMERA_HOLDER_PIN"),
                Config("constants", "STANDARD_SERVO_MIN_VALUE")
                Config("constants", "STANDARD_SERVO_MAX_VALUE")
                );
    }

    void Robot::move(float distance_forward, float turn) {
    }

    void Robot::stop(void) {
    }
}
