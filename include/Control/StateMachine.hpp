//
// Created by Herman Hårstad Gran on 24/02/2024.
//

#ifndef LINEFOLLOWERROBOT_STATEMACHINE_HPP
#define LINEFOLLOWERROBOT_STATEMACHINE_HPP

#include "Control/Sensors.hpp"
#include "Arduino.h"
#include "QTRSensors.h"
#include "Motor/Motor.hpp"
#include "PID/PID.hpp"
#include "Control/SensorReadings.hpp"
#include <algorithm>
#include "Control/RobotOdometry.hpp"
#include "Control/Button.hpp"

/**
 * Class for deciding what state
 * Currently if-else
 * Will change to switch case
 */
class StateMachine {
public:
    /**
     * Constructor for StateMachine
     * @param pid_ Takes in a PID class, used for pid calculations
     * @param motorA_ Takes in right motor
     * @param motorB_ Takes in left motor
     */
    StateMachine(PID &pid_, Motor &motorA_, Motor &motorB_, RobotOdometry &odometry, Button &button);

    /**
     * Function for changing state of robot, currently if-else
     * @param sensorValues_ Takes in a pointer to the sensor values
     * @param position_ Takes in the position of the line relative to the sensor
     */
    void state(uint16_t position_, bool toggleState);

    /**
     * Self made function for clamp
     * @param val Value to clamp
     * @param minVal Min value range
     * @param maxVal Max value range
     * @return Clamped value
     */
    static int clamp(int val, int minVal, int maxVal);

    /**
     * Initializing turn speeds for corners
     * @param rightMotorA
     * @param leftMotorA
     * @param rightMotorB
     * @param leftMotorB
     */
    void setTurnSpeed(int rightMotorA, int leftMotorA, int rightMotorB, int leftMotorB);

    /**
     * Sets right turn speed for motor A
     * @param speed desired speed value
     */
    void setRightTurnSpeedMotorA(int speed);

    /**
     * Sets left turn speed for motor A
     * @param speed desired speed value
     */
    void setLeftTurnSpeedMotorA(int speed);

    /**
     * Sets right turn speed for motor B
     * @param speed desired speed value
     */
    void setRightTurnSpeedMotorB(int speed);

    /**
     * Sets left turn speed for motor B
     * @param speed desired speed value
     */
    void setLeftTurnSpeedMotorB(int speed);

    /**
     * Getter function for right turn speed for motor A
     * @return current speed
     */
    int getRightTurnSpeedMotorA() const;

    /**
     * Getter function for left turn speed for motor A
     * @return current speed
     */
    int getLeftTurnSpeedMotorA() const;

    /**
     * Getter function for right turn speed for motor B
     * @return current speed
     */
    int getRightTurnSpeedMotorB() const;

    /**
     * Getter function for left turn speed for motor B
     * @return current speed
     */
    int getLeftTurnSpeedMotorB() const;


private:
    PID &pid;
    Motor &motorA;
    Motor &motorB;
    RobotOdometry &odometry;
    Button &button;

    int rightTurnSpeedMotorA;
    int leftTurnSpeedMotorA;
    int rightTurnSpeedMotorB;
    int leftTurnSpeedMotorB;

    bool turnFunction = false;
};

#endif //LINEFOLLOWERROBOT_STATEMACHINE_HPP
