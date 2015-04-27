namespace constants {
    // Max speed allowed, float between 0 and 1
    const float MAX_SPEED = 1.0F;

    // Stop value used in PWM to stop the continuous servo
    const int CONTINUOUS_SERVO_STOP_VALUE = 141;
    // Value to send to PWM to go full forward
    const int CONTINUOUS_SERVO_FULL_FORWARD_VALUE = 155;

    // Minimum position for a standard servo, as PWM
    const int STANDARD_SERVO_MIN_VALUE = 78;
    // Maximum position for a standard servo, as PWM
    const int STANDARD_SERVO_MAX_VALUE = 170;

    // Pin of the left wheel, Broadcom numbering
    const int LEFT_WHEEL_PIN = 18;
    // Whether this pin is a hard pwm or not
    const bool LEFT_WHEEL_IS_HARD_PWM = true;
    // A float reduction factor used to compensate differences
    // between the wheels
    const float LEFT_WHEEL_REDUCTION_FACTOR = 1.0F;

    // Pin of the right wheel, Broadcom numbering
    const int RIGHT_WHEEL_PIN = 13;
    // Whether this pin is a hard pwm or not
    const bool RIGHT_WHEEL_IS_HARD_PWM = true;
    // A float reduction factor used to compensate differences
    // between the wheels
    const float RIGHT_WHEEL_REDUCTION_FACTOR = 1.0F;

    // Pin for the camera holder, Broadcom numbering
    const int CAMERA_HOLDER_PIN = 17;
    // Whether this pin is a hard PMW or not
    const bool CAMERA_HOLDER_IS_HARD_PWM = false;
    // Software low stop for the camera holder
    const int CAMERA_HOLDER_LOW_STOP = 0;
    // Software high stop for the camera holder
    const int CAMERA_HOLDER_HIGH_STOP = 180;

    // UDP port to listen on
    const int LISTENING_PORT = 4242;
}
