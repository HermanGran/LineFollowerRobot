//
// Created by Herman Hårstad Gran on 05/02/2024.
//

#ifndef LINEFOLLOWERROBOT_SENSORS_HPP
#define LINEFOLLOWERROBOT_SENSORS_HPP

#include <Arduino.h>
#include <QTRSensors.h>

class Sensors {
public:
    /**
     * Constructor for initializing sensor
     * @param numSensors Number of sensors in use
     */
    Sensors(int sensorCount_, QTRSensors& qtr_);

    /**
     * Setting up sensor
     */
    void setup();

    /**
     * Calibrating sensor
     */
    void calibrate();

    QTRSensors& getQTRSensor();

private:
    const uint8_t sensorCount;
    QTRSensors& qtr;
};

#endif //LINEFOLLOWERROBOT_SENSORS_HPP
