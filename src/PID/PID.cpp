#include "PID/PID.hpp"

// Constructor for PID class
PID::PID(double kP_, double kI_, double kD_, int baseSpeed_, int maxSpeed_, int targetPosition_) : kP(kP_), kI(kI_), kD(kD_), baseSpeed(baseSpeed_), maxSpeed(maxSpeed_), targetPosition(targetPosition_) {}

// Calculates wanted motor speed
int PID::calculatePID(uint16_t position_) {

    int error = targetPosition - position_;

    double P = error;
    double I = I + error;
    double D = error - lastError;
    lastError = error;

    motorSpeed = (P * kP) + (I * kI) + (D * kD);

    return motorSpeed;
}

// Returns base speed
int PID::getBaseSpeed() const {
    return baseSpeed;
}

// Returns max speed
int PID::getMaxSpeed() const {
    return maxSpeed;
}

// Returns target position
int PID::getTargetPosition() const {
    return targetPosition;
}