#include "Control/StateMachine.hpp"

//For sensor
QTRSensors qtr;
Sensors sensor(9, qtr);
uint16_t sensorValues[9];
SensorReadings sensorReadings(50);

// Motors
Motor motorA(20, 19, 18);
Motor motorB(21, 22, 23);

// PID class
PID pid(90,    // Base Speed
        90,    // Max Speed
        4000);  // Target Position

// Initializes state machine
StateMachine stateMachine(pid, motorA, motorB);

void setup() {
    Serial.begin(9600);
    // Setting PID values P, I, D
    pid.setPID(13, 0, 0.5);
    pid.setAggressivePID(20, 0, 0);

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

    //stateMachine.state(sensorValues, position);
    stateMachine.newState(sensorValues, position, sensorReadings);
}