//
// Created by Herman Hårstad Gran on 23/04/2024.
//

#ifndef LINEFOLLOWERROBOT_ROBOTBLE_HPP
#define LINEFOLLOWERROBOT_ROBOTBLE_HPP

#include "Arduino.h"
#include "ArduinoBLE.h"
#include "Control/StateMachine.hpp"
#include "PID/PID.hpp"

/**
 * RobotBLE class is used for connecting the Arduino to bluetooth
 */
class RobotBLE {
public:
    /**
     * Constructor for RobotBLE class
     * @param pid Takes inn reference to a PID class
     */
    RobotBLE(PID &pid);

    /**
     *
     * Initializes the RobotBLE class
     */
    void setup();

    /**
     * Sends the current calculated position to a supported BLE (Bluetooth Low Energy) device
     * @param x X-coordinate
     * @param y Y-coordinate
     * @param theta Orientation
     */
    void updatePosition(float x, float y, float theta);

    /**
     * Updates PID values from BLE device, currently not working
     */
    void updatePID();

private:
    PID &pid;

    BLEService *positionService;
    BLEStringCharacteristic *positionCharacteristic;

    BLEService *pidService;
    BLEFloatCharacteristic *pCharacteristic;
    BLEFloatCharacteristic *iCharacteristic;
    BLEFloatCharacteristic *dCharacteristic;

    float pValue, iValue, dValue;
    int update;
};

#endif //LINEFOLLOWERROBOT_ROBOTBLE_HPP
