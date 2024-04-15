//
// Created by Herman Hårstad Gran on 24/02/2024.
//

#include "Control/StateMachine.hpp"

// Constructor for state machine class
StateMachine::StateMachine(PID &pid_, Motor &motorA_, Motor &motorB_) : pid(pid_), motorA(motorA_), motorB(motorB_) {}

// Function for changing state
void StateMachine::state(const uint16_t *sensorValues_, uint16_t position_) {

    // Calculates motor speed
    int overLine = 0;
    if ( (position_ > 7000) or (position_ < 2000 )) {
        overLine = 1;
    }

    int motorSpeedA = pid.getBaseSpeed() + pid.calculatePID(position_, overLine);
    int motorSpeedB = pid.getBaseSpeed() - pid.calculatePID(position_, overLine);

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
    if (position_ == 0) {
        motorA.reverse(20);
        motorB.reverse(200);
    } else if (position_ == 8000) {
        motorA.reverse(200);
        motorB.reverse(20);
    } else {
        motorA.forward(motorSpeedA);
        motorB.forward(motorSpeedB);
    }
}