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
    if (((sensorValues_[0] > 600) && (sensorValues_[2] > 600)) && ((sensorValues_[6] < 200) && (sensorValues_[8] < 200)))  {
        motorA.forward(255);
        motorB.reverse(170);
        delay(150);
    } else if (((sensorValues_[6] > 600) && (sensorValues_[8] > 600)) && ((sensorValues_[0] < 200) && (sensorValues_[2] < 200))) {
        motorA.reverse(170);
        motorB.forward(255);
        delay(150);
    } else {
        motorA.forward(motorSpeedA);
        motorB.forward(motorSpeedB);
    }
}