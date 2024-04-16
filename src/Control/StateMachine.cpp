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
    clamp(motorSpeedA, 0, pid.getMaxSpeed());
    clamp(motorSpeedB, 0, pid.getMaxSpeed());

    // Current state machine (if-else)
    // Will convert to switch cases
    /*
    if (position_ == 0) {
        motorA.forward(40);
        motorB.reverse(180);
    } else if (position_ == 8000) {
        motorA.reverse(180);
        motorB.forward(40);
    } else {
        motorA.forward(motorSpeedA);
        motorB.forward(motorSpeedB);
    }
    */
    motorA.forward(motorSpeedA);
    motorB.forward(motorSpeedB);

}

void StateMachine::newState(const uint16_t *sensorValues_, uint16_t position_, SensorReadings &sensorReadings_) {

    sensorReadings_.add(position_);
    int deviation = abs(pid.getTargetPosition() - sensorReadings_.getAverage()) / 15;

    int linePos = 0;
    if ( (position_ > 7000) or (position_ < 2000 )) {
        linePos = 1;
    }

    int motorSpeedA = (pid.getBaseSpeed() + deviation) + pid.calculatePID(position_, linePos);
    int motorSpeedB = (pid.getBaseSpeed() + deviation) - pid.calculatePID(position_, linePos);

    clamp(motorSpeedA, 0, pid.getMaxSpeed());
    clamp(motorSpeedB, 0, pid.getMaxSpeed());

    motorA.forward(motorSpeedA);
    motorB.forward(motorSpeedB);
}

int StateMachine::clamp(int val, int minVal, int maxVal) {
    if (val < minVal) return minVal;
    else if (val > maxVal) return maxVal;
    else return val;
}