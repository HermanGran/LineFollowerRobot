#include "Control/StateMachine.hpp"
#include "Motor/Encoder.hpp"
#include "Control/RobotOdometry.hpp"
#include "Control/Button.hpp"
#include "WiFi and BLE/RobotServer.hpp"
// IP address: 172.20.10.4

//For sensor
Sensors sensor(9);
uint16_t sensorValues[9];

// Base speed | Max speed | Target position
PID pid(140, 140, 4000);

// Motors
Motor motorA(18, 19, 17);
Motor motorB(22, 21, 20);

// Button
Button button(13, 50);

// Odometry for calculating world position | Wheelbase distance
RobotOdometry odometry(14.5);

// Initializes state machine
StateMachine stateMachine(pid, motorA, motorB, odometry, button);

// Server
RobotServer server("HermaniPhone", "vanskelig", pid, stateMachine);

void setup() {
    Serial.begin(115200);

    // Setting PID values P, I, D
    pid.setPID(15, 0, 30);
    pid.setAggressivePID(20, 0, 0);

    // Setting turn speed values
    stateMachine.setTurnSpeed(-150, -40, -40, -150);

    // Setup
    button.setup();
    server.setup();

    motorA.setup();
    motorB.setup();

    sensor.setup();
    sensor.calibrate();
}

void loop() {
    server.update();

    uint16_t position = sensor.getQTRSensor()->readLineBlack(sensorValues);
    stateMachine.state(position, button.readState());
}