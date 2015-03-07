namespace servo {
    class Servo {
        public:
            virtual Servo(int pin);
            /**
            * Get the pin on which the servo is attached.
            */
            int getPin(void);
        protected:
        private:
            int pin_;  /** Servo pin. */
            const int range_ = 100;  /** Internal range for the soft PWM. */
    }


    class StandardServo : public Servo {
        public:
            /**
            * Construct a Servo object on specified pin.
            */
            StandardServo(int pin, int min_value, int max_value);

            /**
            * Get the current servo position.
            */
            int getPosition(void);

            /**
            * Move the servo to specified position
            */
            void move(int position);
        protected:
        private:
            int position_;  /** Position of the servo. */
            int min_value_;  /** Minimal angle of the servo. */
            int max_value_;  /** Maximal angle of the servo. */
    }


    class ContinuousServo : public Servo {
        public:
            /**
            * Construct a Servo object on specified pin.
            */
            ContinuousServo(int pin, int stop_value, int full_forward_value);

            /**
            * Get the current servo speed.
            * Speed is 1 for full speed forward, and -1 for full speed backward.
            */
            float getSpeed(void);

            /**
            * Set the servo speed.
            * Speed is 1 for full speed forward, and -1 for full speed backward.
            */
            void setSpeed(float speed);
        protected:
        private:
            float speed_;  /** Speed of the servo. */
            int stop_value_;  /** Value for the stop position of the servo. */
            int full_forward_value_;  /** Value for full speed forward. */
    }
}
