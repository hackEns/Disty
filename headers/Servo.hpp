namespace servo {
    const int DEFAULT_RANGE_SOFT_PWM = 100;
    const int HARD_PWM_RANGE = 1024;


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
            * @param[in] min_angle is the min angle of the servo
            * @param[in] max_angle is the max angle of the servo
            * @param[în] is_hard_pwm defines whether the pwm on the pin is hard or not
            */
            StandardServo(const int pin, const int min_angle, const int max_angle, const bool is_hard_pwm);

            /**
            * Get the current servo position.
            */
            int getPosition(void) const;

            /**
            * Move the servo to specified position
            *
            * @param[in] position is the absolute position, between min and max value.
            */
            void setPosition(const int position);
        protected:
        private:
            int position_;  /** Position of the servo. */
            int min_angle_;  /** Minimal angle of the servo. */
            int max_angle_;  /** Maximal angle of the servo. */
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
