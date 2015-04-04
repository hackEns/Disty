#include <wiringPi.h>
#include <softPwm.h>

#include "Servo.hpp"


namespace servo {
    Servo::Servo(const int pin) : pin_(pin) {
        if (0 != softPwmCreate(pin, 0, range_)) {
            throw std::runtime_error("Unable to initialize Servo.");
        }
    }

    Servo::~Servo(void) {
        // Empty on purpose
    }


    int Servo::getPin(void) {
        return pin_;
    }


    StandardServo::StandardServo(const int pin, const int min_value, int max_value, bool is_hard_pwm)
        : Servo(pin), position_(0), min_value_(min_value), max_value_(max_value), is_hard_pwm_(is_hard_pwm)
    {
        // Empty on purpose
    }


    int StandardServo::getPosition(void) const {
        return position_;
    }


    void StandardServo::move(const int position) {
        int value = (position - min_value) / (max_value - min_value) * 100;

        if (is_hard_pwm_) {
            pwmWrite(pin_, value);
        } else {
            softPwmWrite(pin_, value);
        }
        position_ = position;
    }



    ContinuousServo::ContinuousServo(const int pin, const int stop_value, const int full_forward_value, const bool is_hard_pwm)
        : Servo(pin), speed_(0), stop_value_(stop_value), full_forward_value_(full_forward_value), is_hard_pwm_(is_hard_pwm)
    {
        // Empty on purpose
    }


    float ContinuousServo::getSpeed(void) const {
        return speed_;
    }


    void ContinuousServo::setSpeed(const float speed) {
        if (speed > 1.) {
            speed = 1.;
        }
        else if (speed < -1.) {
            speed = -1.;
        }
        int value = static_cast<int>((full_forward_value - stop_value) * speed);
        if (is_hard_pwm_) {
            pwmWrite(pin_, value);
        } else {
            softPwmWrite(pin_, value);
        }
        speed_ = speed;
    }
}
