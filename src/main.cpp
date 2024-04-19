#include "Control/StateMachine.hpp"

//For sensor
QTRSensors qtr;
Sensors sensor(9, qtr);
uint16_t sensorValues[9];
SensorReadings sensorReadings(70);

// Motors
Motor motorA(20, 19, 18);
Motor motorB(21, 22, 23);

// PID class
PID pid(110,    // Base Speed
        110,    // Max Speed
        4000);  // Target Position

// Initializes state machine
StateMachine stateMachine(pid, motorA, motorB);

void setup() {
    Serial.begin(9600);
    // Setting PID values P, I, D
    pid.setPID(15, 0, 0.5);
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