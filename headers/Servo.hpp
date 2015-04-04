namespace servo {
    class Servo {
        public:
            virtual Servo(const int pin) {};
            virtual ~Servo(void);

            /**
            * Get the pin on which the servo is attached.
            */
            int getPin(void) const;
        protected:
        private:
            int pin_;  /** Servo pin. */
            const int range_ = 100;  /** Internal range for the PWM. */
    };


    class StandardServo : public Servo {
        public:
            /**
            * Construct a Servo object on specified pin.
            */
            StandardServo(const int pin, const int min_value, const int max_value, const bool is_hard_pwm);

            /**
            * Get the current servo position.
            */
            int getPosition(void) const;

            /**
            * Move the servo to specified position
            */
            void setPosition(const int position);
        protected:
        private:
            int position_;  /** Position of the servo. */
            int min_value_;  /** Minimal angle of the servo. */
            int max_value_;  /** Maximal angle of the servo. */
            bool is_hard_pwm_;  /** Whether it is a hard PWM pin or not. */
    };


    class ContinuousServo : public Servo {
        public:
            /**
            * Construct a Servo object on specified pin.
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
            void setSpeed(const float speed);
        protected:
        private:
            float speed_;  /** Speed of the servo. */
            int stop_value_;  /** Value for the stop position of the servo. */
            int full_forward_value_;  /** Value for full speed forward. */
            bool is_hard_pwm_;  /** Whether it is a hard PWM pin or not. */
    };
}
