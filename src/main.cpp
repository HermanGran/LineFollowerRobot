#include "Control/StateMachine.hpp"
#include "Motor/Encoder.hpp"
#include "Control/RobotOdemetry.hpp"

//For sensor
QTRSensors qtr;
Sensors sensor(9, qtr);
uint16_t sensorValues[9];
SensorReadings sensorReadings(70);

// Motors and Encoders
Encoder EncoderMotorA(17, 13);
Encoder EncoderMotorB(24, 1);

Motor motorA(20, 19, 18, EncoderMotorA);
Motor motorB(21, 22, 23, EncoderMotorB);

// PID class
PID pid(100,    // Base Speed
        100,    // Max Speed
        4000);  // Target Position

RobotOdemetry odemetry(16.0);

// Initializes state machine
StateMachine stateMachine(pid, motorA, motorB, odemetry);

void setup() {
    Serial.begin(9600);

    // Setting PID values P, I, D
    pid.setPID(18, 0, 0.5);
    pid.setAggressivePID(20, 0, 0);

    // Motor setup
    motorA.setup();
    motorB.setup();

    // Encoder Setup
    EncoderMotorA.begin();
    EncoderMotorB.begin();

    // Sensor setup
    sensor.setup();
    sensor.calibrate();
}

void loop() {

    microsecondsToClockCycles(100);
    // Reads sensor value
    uint16_t position = qtr.readLineBlack(sensorValues);

    stateMachine.newState(sensorValues, position, sensorReadings);

    Serial.println();
}