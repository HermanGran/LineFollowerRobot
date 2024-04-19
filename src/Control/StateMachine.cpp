//
// Created by Herman Hårstad Gran on 24/02/2024.
//

#include "Control/StateMachine.hpp"

// Constructor for state machine class
StateMachine::StateMachine(PID &pid_, Motor &motorA_, Motor &motorB_) : pid(pid_), motorA(motorA_), motorB(motorB_) {}

// Function for changing state
void StateMachine::state(const uint16_t *sensorValues_, uint16_t position_) {

    // Calculates motor speed
    int linePos = 0;
    if ( (position_ > 7000) or (position_ < 2000 )) {
        linePos = 1;
    }

    int motorSpeedA = clamp(pid.getBaseSpeed() + pid.calculatePID(position_, linePos), 0, pid.getMaxSpeed());
    int motorSpeedB = clamp(pid.getBaseSpeed() - pid.calculatePID(position_, linePos), 0, pid.getMaxSpeed());

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
    int deviation = abs(pid.getTargetPosition() - sensorReadings_.getAverage()) / 75;

    int linePos = 0;
    if ((position_ > 6500) or (position_ < 1500 )) {
        linePos = 1;
        digitalWrite(14, LOW);
        digitalWrite(15, LOW);
        deviation = deviation*0;
    } else {
        linePos = 0;
        digitalWrite(14, HIGH);
        digitalWrite(15, HIGH);
    }


    int motorSpeedA = clamp(pid.getBaseSpeed() + pid.calculatePID(position_, 0), 0, pid.getMaxSpeed());
    int motorSpeedB = clamp(pid.getBaseSpeed() - pid.calculatePID(position_, 0), 0, pid.getMaxSpeed());

    motorA.forward(motorSpeedA + deviation);
    motorB.forward(motorSpeedB + deviation);

    /*
    Serial.print("Position: ");
    Serial.print(position_);
    Serial.print("      Average: ");
    Serial.print(sensorReadings_.getAverage());
    Serial.print("      Difference: ");
    Serial.println(abs(sensorReadings_.getAverage() - position_));
    */

    if (position_ == 0) {
        motorA.forward(110);
        motorB.forward(15);
    } else if (position_ == 8000) {
        motorA.forward(15);
        motorB.forward(110);
    }
}

int StateMachine::clamp(int val, int minVal, int maxVal) {
    if (val < minVal) return minVal;
    else if (val > maxVal) return maxVal;
    else return val;
}