#include "Servo.hpp"
#include "UDPServer.hpp"

namespace robot {
    class Robot {
        public:
            /** Construct a Robot object. */
            Robot(void);

            /** Stop the robot on object destruction. */
            ~Robot(void);

            /** Move the robot. */
            void move(float speed);

            /** Stop moving. */
            void stop(void);

            /** Look at the specified point.
             * @param angle  an angle between CAMERA_HOLDER_LOW_STOP and CAMERA_HOLDER_HIGH_STOP */
            void lookAt(int angle);

            /** Listen for and handle the commands received through the UDPServer. */
            void listen(void);
        private:
            servo::ContinuousServo left_wheel_;
            servo::ContinuousServo right_wheel_;

            servo::StandardServo camera_holder_;

            udpserver::UDPServer server_;
    };
}
