//
// Created by Herman Hårstad Gran on 22/01/2024.
//

#ifndef LINEFOLLOWERROBOT_MOTORS_HPP
#define LINEFOLLOWERROBOT_MOTORS_HPP

#include <Arduino.h>
#include "Motor/Encoder.hpp"

/**
 * Motor class for initialising and driving motors
 */
class Motor{
public:
    /**
     * Constructor for motor class
     * @param input_ Input pin for motor
     * @param output_ Output pin for motor
     * @param PWM_ Output pin for PWM motor
     */
    Motor(int input_, int output_, int PWM_);

    void setup();

    /**
     * Function for driving forward
     * @param motorSpeed The wanted speed
     */
    void forward(int motorSpeed_) const;

    /**
     * Function for driving backwards
     * @param motorSpeed_ The wanted speed
     */
    void reverse(int motorSpeed_) const;

    /**
     * Function for stopping motor
     */
    void stop() const;

    void turn(int motorSpeed);

private:
    int input;
    int output;
    int PWM;

};

#endif //LINEFOLLOWERROBOT_MOTORS_HPP
