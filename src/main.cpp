#include "Control/StateMachine.hpp"

//For sensor
QTRSensors qtr;
Sensors sensor(10, qtr);
uint16_t sensorValues[10];

// Motors
Motor motorA(9, 8, 10);
Motor motorB(12, 13, 11);

// PID
PID pid(0.35,   // P
        0,      // I
        0.2,    // D
        120,    // Base Speed
        120,    // Max Speed
        4500);  // Target Position

// Initializes state machine (right now if-else)
StateMachine stateMachine(pid, motorA, motorB);

// Pin for switch
const int switchPin = 7;

void setup() {
    Serial.begin(9600);

    // Switch initialization
    pinMode(switchPin, INPUT_PULLUP);
    pinMode(LED_BUILTIN, OUTPUT);

    // Sensor setup
    sensor.setup();
    sensor.calibrate();
}

void loop() {

    // Reads sensor value
    uint16_t position = qtr.readLineBlack(sensorValues);
    Serial.println(position);

    // Turns of or on according to switch state
    if (digitalRead(7) == LOW) {
        stateMachine.state(sensorValues, position);
    } else {
        motorA.stop();
        motorB.stop();
    }
}
