//
// Created by Herman Hårstad Gran on 05/02/2024.
//

#include "Control/Sensors.hpp"

// Constructor for sensors
Sensors::Sensors(int sensorCount_) : sensorCount(sensorCount_) {
    qtr = new QTRSensors;
}

// Setup for sensors
void Sensors::setup() {
    qtr->setTypeRC();
    qtr->setSensorPins((const uint8_t[]) {4, 5, 6, 7, 8, 9, 10, 11, 12}, sensorCount);
}

// Function for calibrating sensors
void Sensors::calibrate() {

    // LED pinMode
    pinMode(14, OUTPUT);
    pinMode(15, OUTPUT);

    delay(500);
    digitalWrite(14, LOW);

    for (uint16_t i = 0; i < 400; i++) {
        qtr->calibrate();
    }

    digitalWrite(14, HIGH);
    delay(100);
    digitalWrite(15, LOW);
    delay(500);
    digitalWrite(15, HIGH);
    delay(500);
}

// Function for returning reference for QTR
QTRSensors* Sensors::getQTRSensor() {
    return qtr;
}