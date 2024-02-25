//
// Created by Herman Hårstad Gran on 24/02/2024.
//

#include "Control/StateMachine.hpp"

// Constructor for state machine class
StateMachine::StateMachine(PID &pid_, Motor &motorA_, Motor &motorB_) : pid(pid_), motorA(motorA_), motorB(motorB_) {}

// Function for changing state
void StateMachine::state(const uint16_t *sensorValues_, uint16_t position_) {

    // Calculates motor speed
    int motorSpeedA = pid.getBaseSpeed() + pid.calculatePID(position_);
    int motorSpeedB = pid.getBaseSpeed() - pid.calculatePID(position_);

    // Sets speed equal to max
    if (motorSpeedA > pid.getMaxSpeed()) {
        motorSpeedA = pid.getMaxSpeed();
    }
    if (motorSpeedB > pid.getMaxSpeed()) {
        motorSpeedB = pid.getMaxSpeed();
    }
    if (motorSpeedA < 0) {
        motorSpeedA = 0;
    }
    if (motorSpeedB < 0) {
        motorSpeedB = 0;
    }

    // Current state machine (if-else)
    // Will convert to switch cases
    if (((sensorValues_[0] > 700) && (sensorValues_[2] > 700)) && ((sensorValues_[7] < 700) && (sensorValues_[9] < 700)))  {
        motorA.reverse(150);
        motorB.forward(200);
        delay(100);
    } else if (((sensorValues_[7] > 700) && (sensorValues_[9] > 700)) && ((sensorValues_[0] < 700) && (sensorValues_[2] < 700))) {
        motorA.forward(200);
        motorB.reverse(150);
        delay(100);
    } else {
        motorA.reverse(motorSpeedA);
        motorB.reverse(motorSpeedB);
    }
}