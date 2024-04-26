//
// Created by Herman Hårstad Gran on 31/01/2024.
//

#include "Motor/Motor.hpp"

// Constructor for motor class
Motor::Motor(int input_, int output_, int PWM_) : input(input_), output(output_), PWM(PWM_) {}

// Function for motor setup
void Motor::setup() {
    pinMode(output, OUTPUT);
    pinMode(input, OUTPUT);
    pinMode(PWM, OUTPUT);
}

// Function for spinning motors forward
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

// Function for stopping motor
void Motor::stop() const {
    digitalWrite(input, LOW);
    digitalWrite(output, LOW);
    analogWrite(PWM, 0);
}

void Motor::turn(int motorSpeed) {
    if (motorSpeed < 0) reverse(motorSpeed);
    else forward(motorSpeed);
}
