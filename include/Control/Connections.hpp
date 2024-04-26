//
// Created by Herman Hårstad Gran on 23/04/2024.
//

#ifndef LINEFOLLOWERROBOT_CONNECTIONS_HPP
#define LINEFOLLOWERROBOT_CONNECTIONS_HPP

#include "Arduino.h"
#include "ArduinoBLE.h"
#include "Control/StateMachine.hpp"
#include "PID/PID.hpp"

class Connections {
public:
    Connections(PID &pid);

    void setup();

    void updatePosition(float x, float y, float theta);

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

#endif //LINEFOLLOWERROBOT_CONNECTIONS_HPP
