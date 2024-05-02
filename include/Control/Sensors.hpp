//
// Created by Herman Hårstad Gran on 05/02/2024.
//

#ifndef LINEFOLLOWERROBOT_SENSORS_HPP
#define LINEFOLLOWERROBOT_SENSORS_HPP

#include <Arduino.h>
#include <QTRSensors.h>

/**
 * Sensors class for initializing and reading sensor
 */
class Sensors{
public:
    /**
     * Constructor for initializing sensor
     * @param numSensors Number of sensors in use
     */
    explicit Sensors(int sensorCount_);

    /**
     * Setting up sensor
     */
    void setup();

    /**
     * Calibrating sensor
     */
    void calibrate();

    /**
     * Function for retrieving a reference for QTRSensors
     * @return Reference for QTRSensors
     */
    QTRSensors* getQTRSensor();

    /**
     * Retrieves a pointer to the sensor values
     * @return a pointer to the vector of sensor values
     */
    uint16_t* getSensorValues();

private:
    const uint8_t sensorCount;
    uint16_t sensorValues;
    QTRSensors *qtr;
};

#endif //LINEFOLLOWERROBOT_SENSORS_HPP
