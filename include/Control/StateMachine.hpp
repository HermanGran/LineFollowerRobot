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
    StateMachine(PID &pid_, Motor &motorA_, Motor &motorB_);

    /**
     * Testing new state
     * @param sensorValues_ Takes in a pointer to the sensor values
     * @param position_ Takes in the position of the line relative to the sensor
     */
    void newState(const uint16_t *sensorValues_, uint16_t position_);

    /**
     * Function for changing state of robot, currently if-else
     * @param sensorValues_ Takes in a pointer to the sensor values
     * @param position_ Takes in the position of the line relative to the sensor
     */
    void state(const uint16_t *sensorValues_, uint16_t position_);

private:
    PID &pid;

    Motor &motorA;
    Motor &motorB;
};

#endif //LINEFOLLOWERROBOT_STATEMACHINE_HPP
