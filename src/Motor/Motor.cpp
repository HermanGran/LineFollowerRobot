//
// Created by Herman Hårstad Gran on 31/01/2024.
//

#include "Motor/Motor.hpp"

// Constructor for motor class
Motor::Motor(int input_, int output_, int PWM_) : input(input_), output(output_), PWM(PWM_) {}

void Motor::spinMotor(float pwm_) {

    float pwr = fabs(pwm_);
    if (pwr > 120) {
        pwr = 120;
    }

    if (pwm_ < 0) {
        reverse(pwr);
    } else {
        forward(pwr);
    }
}

// Function for spinning motor forward
void Motor::forward(int motorSpeed_) const {
    digitalWrite(input, HIGH);
    digitalWrite(output, LOW);
    analogWrite(PWM, motorSpeed_);
}

// Function for spinning motor in reverse
void Motor::reverse(int motorSpeed_) const {
    digitalWrite(input, LOW);
    digitalWrite(output, HIGH);
    analogWrite(PWM, motorSpeed_);
}

void Motor::stop() const {
    digitalWrite(input, LOW);
    digitalWrite(output, LOW);
    analogWrite(PWM, 0);
}