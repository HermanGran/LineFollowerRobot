//
// Created by Herman Hårstad Gran on 24/02/2024.
//

#include "Control/StateMachine.hpp"

// Constructor for state machine class
StateMachine::StateMachine(PID &pid_, Motor &motorA_, Motor &motorB_, RobotOdometry &odometry, Button &button) : pid(pid_), motorA(motorA_), motorB(motorB_), odometry(odometry), button(button) {}

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

void StateMachine::newState(uint16_t position_) {

    bool run = button.readState();

    odometry.logPosition(odometry.getX(), odometry.getY());

    if ((odometry.checkLapCompletion(odometry.getX(), odometry.getY(), 20)) && (odometry.getPath().size() > 1000)) {
        digitalWrite(14, LOW);
    }
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

    if (run) {

        if (position_ == 0) {
            motorA.forward(150);
            motorB.reverse(40);
        } else if (position_ == 8000) {
            motorA.reverse(40);
            motorB.forward(150);
        } else {
            motorA.forward(motorSpeedA);
            motorB.forward(motorSpeedB);
        }

        //motorA.forward(motorSpeedA);
        //motorB.forward(motorSpeedB);
    } else {
        motorA.stop();
        motorB.stop();
    }



}

int StateMachine::clamp(int val, int minVal, int maxVal) {
    if (val < minVal) return minVal;
    else if (val > maxVal) return maxVal;
    else return val;
}

PID& StateMachine::getPID() {
    return pid;
}