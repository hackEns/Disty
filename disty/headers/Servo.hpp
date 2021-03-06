namespace servo {
    const int DEFAULT_RANGE_SOFT_PWM = 50;  // 50Hz

    // These constants are computed so that the base frequency is 20ms (for
    // servos) and the 1.5ms pulse is a valid int multiple. This means:
    // * 19.2 MHz / (CLOCK * RANGE) = 50Hz (19.2MHz being the base frequency of
    // the PWM clock in the raspi).
    // * There exists a valid int such that pwmWrite(pin, INT) is a 1.5ms pulse
    // (which is the stop position, or middle position for standard servo, and
    // servos are supposed to be symmetric with respect to this position).
    const int HARD_PWM_CLOCK = 200;
    const int HARD_PWM_RANGE = 1920;

    // The minimum pulse width is 100µs. If we take a range of 100, this gives
    // us 100 * 100 = 10^4 µs or a frequency of 100Hz. A servo is controlled
    // with 20ms pulses, or a frequency of 50Hz, then the range is 200.
    const int SOFT_PWM_RANGE = 200;


    class Servo {
        public:
            /**
            * Construct a Servo object on specified pin.
            *
            * @param[in] pin is the pin on which the servo is attached.
            * @param[în] is_hard_pwm defines whether the pwm on the pin is hard or not
            */
            Servo(const int pin, const bool is_hard_pwm);
            virtual ~Servo(void);

            /**
            * Get the pin on which the servo is attached.
            */
            int getPin(void) const;

            /**
             * Write zero to the soft PWM. Used for preventing
             * servo jittering once target is reached.
             */
            void writeZeroSoftPWM(void);
        protected:
            int pin_;  /** Servo pin. */
            int range_;  /** Internal range for the PWM. */
            bool is_hard_pwm_;  /** Whether it is a hard PWM pin or not. */
        private:
    };


    class StandardServo : public Servo {
        public:
            /**
            * Construct a StandardServo object on specified pin.
            *
            * @param[in] pin is the pin on which the servo is attached.
            * @param[in] min_angle is the min angle of the servo, expressed in
            *            units of PWM range (and *not* in degrees / rads)
            * @param[in] max_angle is the max angle of the servo, expressed in
            *            units of PWM range (and *not* in degrees / rads)
            * @param[in] average_speed is the average speed of the servo in
            *            rounds per seconds. Used when software PWM is used, to
            *            prevent jittering.
            * @param[în] is_hard_pwm defines whether the pwm on the pin is hard or not
            */
            StandardServo(const int pin, const int min_angle, const int max_angle, const float average_speed, const bool is_hard_pwm);

            /**
            * Get the current servo position.
            */
            int getPosition(void) const;

            /**
            * Move the servo to specified position
            *
            * @param[in] position is the expected position of the servo, in
            *            degrees between 0 and 180.
            */
            void setPosition(const int position);
        protected:
        private:
            int position_;  /** Position of the servo. */
            int min_angle_;  /** Minimal angle of the servo. */
            int max_angle_;  /** Maximal angle of the servo. */
            float average_speed_;  /** Average speed of the servo, in rounds per seconds. */
    };


    class ContinuousServo : public Servo {
        public:
            /**
            * Construct a Servo object on specified pin.
            *
            * @param[in] pin is the pin on which the servo is attached.
            * @param[în] stop_value is the PWM value corresponding to stop (speed = 0)
            * @param[in] full_forward_value is the PWM value corresponding to full
            *            speed forward.
            * @param[în] is_hard_pwm defines whether the pwm on the pin is hard or not
            *
            * @remark full_forward_value and stop_value must take into account the PWM range!
            */
            ContinuousServo(const int pin, const int stop_value, const int full_forward_value, const bool is_hard_pwm);

            /**
            * Stop the servo on destruction.
            */
            ~ContinuousServo(void);

            /**
            * Get the current servo speed.
            * Speed is 1 for full speed forward, and -1 for full speed backward.
            */
            float getSpeed(void) const;

            /**
            * Set the servo speed.
            * Speed is 1 for full speed forward, and -1 for full speed backward.
            */
            void setSpeed(float speed);
        protected:
        private:
            float speed_;  /** Speed of the servo. */
            int stop_value_;  /** PWM value for the stop position of the servo. */
            int full_forward_value_;  /** PWM value for full speed forward. */
    };
}
