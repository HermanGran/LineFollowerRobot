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
     * @param baseSpeed_ Sets base speed
     * @param maxSpeed_ Sets max speed
     * @param targetPosition_ Sets target position for PID
     */
    PID(int baseSpeed_, int maxSpeed_, int targetPosition_);

    /**
     * Setting PID Values
     * @param kP_ Sets P value
     * @param kI_ Sets I value
     * @param kD_ Sets D value
     */
    void setPID(double kP_, double kI_, double kD_);

    /**
     * Setting aggressive PID values
     * @param aggressiveP_ Sets P value
     * @param aggressiveI_ Sets I value
     * @param aggressiveD_ Sets D value
     */
    void setAggressivePID(double aggressiveP_, double aggressiveI_, double aggressiveD_);

    /**
     * Function for calculating wanted motor speed
     * @param position_ Takes in current position over line
     * @return returns motor speed
     */
    float calculatePID(uint16_t position_, int aggressive);

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

    /**
     * Getter function for P value
     * @return Current P value
     */
    int getPValue() const;

    /**
     * Getter function for I value
     * @return Current I value
     */
    int getIValue() const;

    /**
     * Getter function for D value
     * @return Current D value
     */
    int getDValue() const;

    /**
     * Setter function for P value
     * @param value New P value
     */
    void setPValue(float value);

    /**
     * Setter function for I value
     * @param value New I value
     */
    void setIValue(float value);

    /**
     * Setter function for D value
     * @param value New D value
     */
    void setDValue(float value);

    /**
     * Setter function for motor speed
     * @param speed New speed
     */
    void setMotorSpeed(int speed);

private:
    double kP;
    double kI;
    double kD;

    double aggressiveP;
    double aggressiveI;
    double aggressiveD;

    double lastError;

    int baseSpeed;
    int maxSpeed;
    int motorSpeed = 0;

    const int targetPosition;
    int position;

    unsigned long prevT = 0;
    float ePrev = 0;
    float eIntegral = 0;
};

#endif //LINEFOLLOWERROBOT_PID_HPP
