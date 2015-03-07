#include "Servo.hpp"
#include "Config.hpp"

namespace robot {
    class Robot {
        public:
            /** Construct a Robot object. */
            Robot(void);

            /** Move the robot. */
            void move(float distance_forward, float turn);

            /** Stop everything. */
            void stop(void);
        protected:
        private:
            config::Config;

            servo::ContinuousServo wheel_left_;
            servo::ContinuousServo wheel_right_;

            servo::StandardServo camera_holder_;
    }
}
