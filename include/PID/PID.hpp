//
// Created by Herman Hårstad Gran on 22/01/2024.
//

#ifndef LINEFOLLOWERROBOT_PID_HPP
#define LINEFOLLOWERROBOT_PID_HPP

/**
 * PID class is for defining the values and computing
 */
#include "Control/Sensors.hpp"

class PID{
public:
    /**
     * Constructor for PID class
     * @param kP_ Sets P value
     * @param kI_ Sets I value
     * @param kD_ Sets D value
     * @param baseSpeed_ Sets base speed
     * @param maxSpeed_ Sets max speed
     * @param targetPosition_ Sets target position for PID
     */
    PID(double kP_, double kI_, double kD_, int baseSpeed_, int maxSpeed_, int targetPosition_);

    /**
     * Function for calculating wanted motor speed
     * @param position_ Takes in current position over line
     * @return returns motor speed
     */
    int calculatePID(uint16_t position_);

    /**
     * Function for retrieving base speed
     * @return base speed
     */
    int getBaseSpeed() const;

    /**
     * Function for retrieving max speed
     * @return max speed
     */
    int getMaxSpeed() const;

    /**
     * Function for retrieving target position
     * @return Target position
     */
    int getTargetPosition() const;

private:
    const double kP;
    const double kI;
    const double kD;

    double lastError;

    const int baseSpeed;
    const int maxSpeed;
    int motorSpeed = 0;

    const int targetPosition;
    int position;
};

#endif //LINEFOLLOWERROBOT_PID_HPP
