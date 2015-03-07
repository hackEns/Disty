#include "Servo.hpp"
#include "Config.hpp"

namespace robot {
    class Robot {
        public:
            /** Construct a Robot object. */
            Robot(void);

            /** Move the robot. */
            void move(float distance_forward, float turn);

            /** Turn on itself. */
            void turn(float turn);

            /** Stop everything. */
            void stop(void);

            /** Look at the specified point. */
            void lookAt(void);
        protected:
        private:
            config::Config;

            servo::ContinuousServo left_wheel_;
            servo::ContinuousServo right_wheel_;

            servo::StandardServo camera_holder_;
    }
}
