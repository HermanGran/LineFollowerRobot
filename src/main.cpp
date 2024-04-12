#include "Control/StateMachine.hpp"

//For sensor
QTRSensors qtr;
Sensors sensor(9, qtr);
uint16_t sensorValues[9];

// Motors
Motor motorA(20, 19, 18);
Motor motorB(21, 22, 23);

// PID
PID pid(17,   // P
        0,      // I
        6,    // D
        100,    // Base Speed
        100,    // Max Speed
        40);  // Target Position

// Initializes state machine (right now if-else)
StateMachine stateMachine(pid, motorA, motorB);

// Pin for switch
//const int switchPin = 7;

void setup() {

    // Motor setup
    motorA.setup();
    motorB.setup();

    // Sensor setup
    sensor.setup();
    sensor.calibrate();
}

void loop() {

    // Reads sensor value
    uint16_t position = qtr.readLineBlack(sensorValues);

    stateMachine.state(sensorValues, position);
}
