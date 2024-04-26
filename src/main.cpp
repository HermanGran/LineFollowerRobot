#include "Control/StateMachine.hpp"
#include "Motor/Encoder.hpp"
#include "Control/RobotOdometry.hpp"
#include "Control/Connections.hpp"
#include "Control/Button.hpp"
#include "WiFi/RobotServer.hpp"

// IP adress: 172.20.10.4

//For sensor
QTRSensors qtr;
Sensors sensor(9, qtr);
uint16_t sensorValues[9];
SensorReadings sensorReadings(70);

PID pid(130,    // Base Speed
        130,    // Max Speed
        4000);  // Target Position



// Motors
Motor motorA(18, 19, 17);
Motor motorB(22, 21, 20);

// PID class


Button button(13, 50);

RobotOdometry odometry(14.5);

// Initializes state machine
StateMachine stateMachine(pid, motorA, motorB, odometry, button);


RobotServer server("HermaniPhone", "vanskelig", pid, stateMachine);
// ---------- Encoder Stuff --------
const int MotorAencoderA = 23;
const int MotorAencoderB = 24;
const int MotorBencoderA = 3;
const int MotorBencoderB = 2;

volatile long encoderACount = 0;
volatile long encoderBCount = 0;
float prevACount = 0;
float prevBCount = 0;

void handleEncoderA();
void handleEncoderB();

void setup() {
    Serial.begin(9600);
    // Setting PID values P, I, D
    pid.setPID(40, 0, 1.5);
    pid.setAggressivePID(20, 0, 0);

    button.setup();

    server.connect();

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
    server.update();

    float dL = encoderACount - prevACount;
    float dR = encoderBCount - prevBCount;
    //odometry.update(dL, dR);

    prevACount = encoderACount;
    prevBCount = encoderBCount;

    // Reads sensor value
    uint16_t position = qtr.readLineBlack(sensorValues);
    stateMachine.newState(position);
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