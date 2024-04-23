//
// Created by Herman Hårstad Gran on 24/02/2024.
//

#include "Control/StateMachine.hpp"

// Constructor for state machine class
StateMachine::StateMachine(PID &pid_, Motor &motorA_, Motor &motorB_, RobotOdometry &odometry) : pid(pid_), motorA(motorA_), motorB(motorB_), odometry(odometry) {}

// Function for changing state
void StateMachine::state(const uint16_t *sensorValues_, uint16_t position_) {

    // Checks to see if aggressive PID is needed
    int linePos = 0;
    if ( (position_ > 7000) or (position_ < 2000 )) {
        linePos = 1;
    }

    // Calculates motor Speed
    int motorSpeedA = clamp(pid.getBaseSpeed() + pid.calculatePID(position_, 0), 0, pid.getMaxSpeed());
    int motorSpeedB = clamp(pid.getBaseSpeed() - pid.calculatePID(position_, 0), 0, pid.getMaxSpeed());

    // Sets the speed for motors
    if (position_ == 0) {
        motorA.reverse(20);
        motorB.reverse(120);
    } else if (position_ == 8000) {
        motorA.reverse(120);
        motorB.reverse(20);
    } else {
        motorA.forward(motorSpeedA);
        motorB.forward(motorSpeedB);
    }
}

void StateMachine::newState(const uint16_t *sensorValues_, uint16_t position_, SensorReadings &sensorReadings_) {

    odometry.logPosition(odometry.getX(), odometry.getY());

    if ((odometry.checkLapCompletion(odometry.getX(), odometry.getY(), 20)) && (odometry.getPath().size() > 1000)) {
        digitalWrite(14, LOW);
    }

    sensorReadings_.add(position_);
    int deviation = abs(pid.getTargetPosition() - sensorReadings_.getAverage()) / 75;
    /*
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
    */

    int motorSpeedA = clamp(pid.getBaseSpeed() + pid.calculatePID(position_, 0), 0, pid.getMaxSpeed());
    int motorSpeedB = clamp(pid.getBaseSpeed() - pid.calculatePID(position_, 0), 0, pid.getMaxSpeed());

    /*
    if (position_ == 0) {
        motorA.forward(100);
        motorB.forward(10);
    } else if (position_ == 8000) {
        motorA.forward(10);
        motorB.forward(100);
    } else {
        motorA.forward(motorSpeedA);
        motorB.forward(motorSpeedB);
    } */
    //motorA.forward(30);
    //motorB.forward(30);

}

int StateMachine::clamp(int val, int minVal, int maxVal) {
    if (val < minVal) return minVal;
    else if (val > maxVal) return maxVal;
    else return val;
}