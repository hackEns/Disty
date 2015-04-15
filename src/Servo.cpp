#include <stdexcept>
#include <wiringPi.h>
#include <softPwm.h>

#include "Servo.hpp"
#include "utilities.hpp"


namespace servo {
    Servo::Servo(const int pin, const bool is_hard_pwm)
        : pin_(pin), range_(HARD_PWM_RANGE), is_hard_pwm_(is_hard_pwm) {
        if (!is_hard_pwm) {
            if (0 != softPwmCreate(pin, 0, range_)) {
                throw std::runtime_error("Unable to initialize Servo.");
            }
            range_ = DEFAULT_RANGE_SOFT_PWM;
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
        // Empty on purpose
    }


    int Servo::getPin(void) const {
        return pin_;
    }


    StandardServo::StandardServo(const int pin, const int min_angle, int max_angle, bool is_hard_pwm)
        : Servo(pin, is_hard_pwm), position_(0), min_angle_(min_angle), max_angle_(max_angle)
    {
        // Empty on purpose
    }


    int StandardServo::getPosition(void) const {
        return position_;
    }


    void StandardServo::setPosition(const int position) {
        const int value = static_cast<int>(utilities::clamp(
                ((position - min_angle_) /
                 (max_angle_ - min_angle_) *
                 range_),
                0,
                range_));
        if (is_hard_pwm_) {
            pwmWrite(pin_, value);
        } else {
            softPwmWrite(pin_, value);
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
