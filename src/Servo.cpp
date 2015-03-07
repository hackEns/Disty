#include <wiringPi.h>
#include <softPwm.h>

#include "Servo.hpp"

namespace servo {
    Servo::Servo(int pin) : pin_(pin) {
        if (0 != softPwmCreate(pin, 0, range_)) {
            throw std::runtime_error("Unable to initialize Servo.");
        }
    }


    int Servo::getPin(void) {
        return pin_;
    }


    StandardServo::StandardServo(int pin, int min_value, int max_value)
        : Servo(pin), position_(0), min_value_(min_value), max_value_(max_value) {
    }


    int StandardServo::getPosition(void) {
        return position_;
    }


    void StandardServo::move(int position) {
        int value = (position - min_value) / (max_value - min_value) * 100;
        softPwmWrite(pin_, value);
        position_ = position;
    }



    ContinuousServo::ContinuousServo(int pin, int stop_value, int full_forward_value)
        : Servo(pin), speed_(0), stop_value_(stop_value), full_forward_value_(full_forward_value) {
    }


    float ContinuousServo::getSpeed(void) {
        return speed_;
    }


    void ContinuousServo::setSpeed(float speed) {
        if (speed > 1.) {
            speed = 1.;
        }
        else if (speed < -1.) {
            speed = -1.;
        }
        float value = (full_forward_value - stop_value) * speed;
        softPwmWrite(pin_, value);
        speed_ = speed;
    }
}
