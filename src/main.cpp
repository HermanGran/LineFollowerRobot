#include "Control/StateMachine.hpp"

//For sensor
QTRSensors qtr;
Sensors sensor(9, qtr);
uint16_t sensorValues[9];

// Motors
Motor motorA(20, 19, 18);
Motor motorB(21, 22, 23);

// PID class
PID pid(120,    // Base Speed
        120,    // Max Speed
        40);  // Target Position

// Initializes state machine
StateMachine stateMachine(pid, motorA, motorB);

void setup() {

    // Setting PID values P, I, D
    pid.setPID(18, 1, 10);
    pid.setAggressivePID(60, 0, 0);

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