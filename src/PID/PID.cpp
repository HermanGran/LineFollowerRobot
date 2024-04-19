#include "PID/PID.hpp"

// Constructor for PID class
PID::PID(int baseSpeed_, int maxSpeed_, int targetPosition_) : baseSpeed(baseSpeed_), maxSpeed(maxSpeed_), targetPosition(targetPosition_) {}

void PID::setPID(double kP_, double kI_, double kD_) {
    kP = kP_;
    kI = kI_;
    kD = kD_;
}

void PID::setAggressivePID(double aggressiveP_, double aggressiveI_, double aggressiveD_) {
    aggressiveP = aggressiveP_;
    aggressiveI = aggressiveI_;
    aggressiveD = aggressiveD_;
}

// Calculates wanted motor speed
float PID::calculatePID(uint16_t position_, int aggressive) {

    unsigned long currT = micros();
    float deltaT = ((float)(currT-prevT))/1.0e6;
    prevT = currT;

    // Error
    double e = ((targetPosition - position_) / 100);

    // Derivative
    float dedt = (e-ePrev)/(deltaT);

    // Integral
    eIntegral = eIntegral + e*deltaT;
    float u;
    // Control signal
    switch (aggressive) {
        case 0:
            u = kP*e + kD*dedt + kI*eIntegral;
            break;
        case 1:
            u = aggressiveP*e + aggressiveD*dedt + aggressiveI*eIntegral;
            break;
        default:
            u = kP*e + kD*dedt + kI*eIntegral;
    }

    ePrev = e;

    return u;
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