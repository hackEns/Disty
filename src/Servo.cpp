#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <wiringPi.h>
#include <softPwm.h>

#include "Servo.hpp"
#include "utilities.hpp"


namespace servo {
    Servo::Servo(const int pin, const bool is_hard_pwm)
        : pin_(pin), range_(HARD_PWM_RANGE), is_hard_pwm_(is_hard_pwm) {
        if (!is_hard_pwm) {
            range_ = DEFAULT_RANGE_SOFT_PWM;
            pinMode(pin, OUTPUT);
            if (0 != softPwmCreate(pin, 0, range_)) {
                throw std::runtime_error("Unable to initialize Servo.");
            }
        }
        else {
            // Set pin as PWM pin
            pinMode(pin, PWM_OUTPUT);

            // Set PWM correctly
            // Set the PWM mode to Mark:Space which is the standard one
            pwmSetMode(PWM_MODE_MS);
            // Set clock and range prefactor to be as Arduino (tweak frequency)
            pwmSetClock(HARD_PWM_CLOCK);
            pwmSetRange(HARD_PWM_RANGE);
        }

    }

    Servo::~Servo(void) {
        // Set the PWM pin as output and write low to be sure to release PWM signal
        pinMode(pin_, OUTPUT);
        digitalWrite(pin_, LOW);
    }


    int Servo::getPin(void) const {
        return pin_;
    }


    void Servo::writeZeroSoftPWM(void) {
        if (!is_hard_pwm_) {
            softPwmWrite(pin_, 0);
        }
    }


    StandardServo::StandardServo(const int pin, const int min_angle, int max_angle, float average_speed, bool is_hard_pwm)
        : Servo(pin, is_hard_pwm), position_(0), min_angle_(min_angle), max_angle_(max_angle), average_speed_(average_speed)
    {
        // Empty on purpose
    }


    int StandardServo::getPosition(void) const {
        return position_;
    }


    void StandardServo::setPosition(const int position) {
        const int value = static_cast<int>(utilities::clamp(
                (((position / 180.) * (max_angle_ - min_angle_)) +
                 min_angle_),
                min_angle_,
                max_angle_));
        if (is_hard_pwm_) {
            pwmWrite(pin_, value);
        } else {
            softPwmWrite(pin_, value);
            // Let the servo move, based on the passed average speed.
            int delay_milliseconds = static_cast<int>(
                    std::abs(position_ - position) /
                    360.0f /
                    average_speed_ *
                    1000);
            utilities::millisleep(std::max(delay_milliseconds, 10));  // 10ms is the time taken by a PWM cycle of wiringPi
            // Stop the soft PWM signal, to prevent jittering. The servo should
            // hold its position.
            //softPwmWrite(pin_, 0);

        }
        position_ = position;
    }



    ContinuousServo::ContinuousServo(const int pin, const int stop_value, const int full_forward_value, const bool is_hard_pwm)
        : Servo(pin, is_hard_pwm), speed_(0), stop_value_(stop_value), full_forward_value_(full_forward_value)
    {
        // Empty on purpose
    }


    ContinuousServo::~ContinuousServo(void)
    {
        setSpeed(0.0F);
    }


    float ContinuousServo::getSpeed(void) const {
        return speed_;
    }


    void ContinuousServo::setSpeed(float speed) {
        speed = utilities::clamp(speed, -1, 1);
        int value = static_cast<int>(
                stop_value_ +
                speed * (full_forward_value_ - stop_value_));
        if (is_hard_pwm_) {
            pwmWrite(pin_, value);
        } else {
            softPwmWrite(pin_, value);
        }
        speed_ = speed;
    }
}  // namespace servo
