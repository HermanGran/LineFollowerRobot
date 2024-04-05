//
// Created by Herman Hårstad Gran on 05/02/2024.
//

#include "Control/Sensors.hpp"

// Constructor for sensors
Sensors::Sensors(int sensorCount_, QTRSensors& qtr_) : sensorCount(sensorCount_), qtr(qtr_) {}

// Setup for sensors
void Sensors::setup() {
    qtr.setTypeRC();
    qtr.setSensorPins((const uint8_t[]) {4, 5, 6, 7, 8, 9, 10, 11, 12}, sensorCount);
}

// Function for calibrating sensors
void Sensors::calibrate() {
    delay(500);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    for (uint16_t i = 0; i < 400; i++) {
        qtr.calibrate();
    }
    digitalWrite(LED_BUILTIN, LOW);

    for (uint8_t i = 0; i < sensorCount; i++) {
        Serial.print(qtr.calibrationOn.minimum[i]);
        Serial.print(' ');
    }
    Serial.println();

    for (uint8_t i = 0; i < sensorCount; i++) {
        Serial.print(qtr.calibrationOn.maximum[i]);
        Serial.print(' ');
    }
    Serial.println();
    Serial.println();
    delay(1000);
}

// Function for returning reference for QTR
QTRSensors& Sensors::getQTRSensor() {
    return qtr;
}