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

    int motorSpeedA = clamp(pid.getBaseSpeed() + pid.calculatePID(position_, 0), 0, pid.getMaxSpeed());
    int motorSpeedB = clamp(pid.getBaseSpeed() - pid.calculatePID(position_, 0), 0, pid.getMaxSpeed());

    if (run) {
        if (turnFunction) {
            if (position_ == 0) {
                motorA.turn(rightTurnSpeedMotorA);
                motorB.turn(rightTurnSpeedMotorB);
            } else if (position_ == 8000) {
                motorA.turn(leftTurnSpeedMotorA);
                motorB.turn(leftTurnSpeedMotorB);
            } else {
                motorA.forward(motorSpeedA);
                motorB.forward(motorSpeedB);
            }
            } else {
            motorA.forward(motorSpeedA);
            motorB.forward(motorSpeedB);
        }
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

void StateMachine::setLeftTurnSpeedMotorA(int speed) {
    leftTurnSpeedMotorA = speed;
    Serial.println(speed);
}

void StateMachine::setRightTurnSpeedMotorA(int speed) {
    rightTurnSpeedMotorA = speed;
    Serial.println(speed);
}

void StateMachine::setLeftTurnSpeedMotorB(int speed) {
    leftTurnSpeedMotorB = speed;
    Serial.println(speed);
}

void StateMachine::setRightTurnSpeedMotorB(int speed) {
    rightTurnSpeedMotorB = speed;
    Serial.println(speed);
}