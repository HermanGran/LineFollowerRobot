#include "Control/StateMachine.hpp"
#include "Motor/Encoder.hpp"
#include "Control/RobotOdometry.hpp"
#include "Control/Connections.hpp"


//For sensor
QTRSensors qtr;
Sensors sensor(9, qtr);
uint16_t sensorValues[9];
SensorReadings sensorReadings(70);

// Motors
Motor motorA(20, 19, 18);
Motor motorB(21, 22, 23);

// PID class
PID pid(100,    // Base Speed
        100,    // Max Speed
        4000);  // Target Position

// For Bluetooth
Connections connections(pid);

RobotOdometry odometry(14.5);

// Initializes state machine
StateMachine stateMachine(pid, motorA, motorB, odometry);

int testMode = 0;


// ---------- Encoder Stuff --------
const int MotorAencoderA = 17;
const int MotorAencoderB = 13;
const int MotorBencoderA = 24;
const int MotorBencoderB = 1;

volatile long encoderACount = 0;
volatile long encoderBCount = 0;
float prevACount = 0;
float prevBCount = 0;

void handleEncoderA();
void handleEncoderB();

void setup() {
    Serial.begin(9600);
    // Setting PID values P, I, D
    pid.setPID(8, 0, 1);
    pid.setAggressivePID(20, 0, 0);

    connections.setup();

    pinMode(MotorAencoderA, INPUT);
    pinMode(MotorAencoderB, INPUT);
    pinMode(MotorBencoderA, INPUT);
    pinMode(MotorBencoderB, INPUT);

    attachInterrupt(digitalPinToInterrupt(MotorAencoderA), handleEncoderA, RISING);
    attachInterrupt(digitalPinToInterrupt(MotorBencoderA), handleEncoderB, RISING);

    // Motor setup
    motorA.setup();
    motorB.setup();

    // Sensor setup
    sensor.setup();
    sensor.calibrate();
}

void loop() {

    float dL = encoderACount - prevACount;
    float dR = encoderBCount - prevBCount;
    odometry.update(dL, dR);

    prevACount = encoderACount;
    prevBCount = encoderBCount;

    // Reads sensor value
    uint16_t position = qtr.readLineBlack(sensorValues);
    stateMachine.newState(sensorValues, position, sensorReadings);

}

void handleEncoderA() {
    if (digitalRead(MotorAencoderA) > digitalRead(MotorAencoderB)) {
        encoderACount++;
    } else {
        encoderACount--;
    }
}

void handleEncoderB() {
    if (digitalRead(MotorBencoderA) > digitalRead(MotorBencoderB)) {
        encoderBCount++;
    } else {
        encoderBCount--;
    }
}