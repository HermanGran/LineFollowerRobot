//
// Created by Herman Hårstad Gran on 24/02/2024.
//

#include "Control/StateMachine.hpp"

// Constructor for state machine class
StateMachine::StateMachine(PID &pid_, Motor &motorA_, Motor &motorB_, RobotOdometry &odometry, Button &button)
: pid(pid_), motorA(motorA_), motorB(motorB_), odometry(odometry), button(button), rightTurnSpeedMotorA(0), leftTurnSpeedMotorA(0), rightTurnSpeedMotorB(0), leftTurnSpeedMotorB(0) {}

// Function for changing state
void StateMachine::state(uint16_t position_, bool toggleState) {

    int motorSpeedA = clamp(pid.getBaseSpeed() + pid.calculatePID(position_, 0), 0, pid.getMaxSpeed());
    int motorSpeedB = clamp(pid.getBaseSpeed() - pid.calculatePID(position_, 0), 0, pid.getMaxSpeed());

    if (toggleState) {
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

// Clamping values between min and max
int StateMachine::clamp(int val, int minVal, int maxVal) {
    if (val < minVal) return minVal;
    else if (val > maxVal) return maxVal;
    else return val;
}

// Initializing speeds for turning in 90 degree corners
void StateMachine::setTurnSpeed(int rightMotorA, int leftMotorA, int rightMotorB, int leftMotorB) {
    turnFunction = true;
    rightTurnSpeedMotorA = rightMotorA;
    leftTurnSpeedMotorA = leftMotorA;
    rightTurnSpeedMotorB = rightMotorB;
    leftTurnSpeedMotorB = leftMotorB;
}

// Sets left turn speed for motor A
void StateMachine::setLeftTurnSpeedMotorA(int speed) {
    leftTurnSpeedMotorA = speed;
}

// Sets right turn speed for motor A
void StateMachine::setRightTurnSpeedMotorA(int speed) {
    rightTurnSpeedMotorA = speed;
}

// Sets left turn speed for motor B
void StateMachine::setLeftTurnSpeedMotorB(int speed) {
    leftTurnSpeedMotorB = speed;
}

// Sets right turn speed for motor B
void StateMachine::setRightTurnSpeedMotorB(int speed) {
    rightTurnSpeedMotorB = speed;
}

// Gets current left turn speed motor A
int StateMachine::getLeftTurnSpeedMotorA() const {
    return leftTurnSpeedMotorA;
}

// Gets current right turn speed motor A
int StateMachine::getRightTurnSpeedMotorA() const {
    return rightTurnSpeedMotorA;
}

// Gets current left turn speed motor B
int StateMachine::getLeftTurnSpeedMotorB() const {
    return leftTurnSpeedMotorB;
}

// Gets current right turn speed motor B
int StateMachine::getRightTurnSpeedMotorB() const {
    return rightTurnSpeedMotorB;
}