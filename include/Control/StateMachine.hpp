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
     * Testing new state
     * @param sensorValues_ Takes in a pointer to the sensor values
     * @param position_ Takes in the position of the line relative to the sensor
     */
    void newState(uint16_t position_);

    /**
     * Function for changing state of robot, currently if-else
     * @param sensorValues_ Takes in a pointer to the sensor values
     * @param position_ Takes in the position of the line relative to the sensor
     */
    void state(const uint16_t *sensorValues_, uint16_t position_);

    /**
     * Self made function for clamp
     * @param val Value to clamp
     * @param minVal Min value range
     * @param maxVal Max value range
     * @return Clamped value
     */
    int clamp(int val, int minVal, int maxVal);

    void setTurnSpeed(int motorA, int motorB);

    PID& getPID();

    Button& getButton();

    void setRightTurnSpeedMotorA(int speed);
    void setLeftTurnSpeedMotorA(int speed);
    void setRightTurnSpeedMotorB(int speed);
    void setLeftTurnSpeedMotorB(int speed);

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
