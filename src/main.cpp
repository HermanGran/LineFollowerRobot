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
//RobotServer server("HermaniPhone", "vanskelig", pid, stateMachine);

void setup() {
    Serial.begin(115200);

    // Setting PID values P, I, D
    //pid.setPID(18, 0, 36);
    //pid.setPID(21, 0, 46);
    pid.setPID(27, 0, 30);
    pid.setAggressivePID(20, 0, 0);

    // Setting turn speed values
    //stateMachine.setTurnSpeed(-40, -120, -120, -40);
    stateMachine.setTurnSpeed(100, -120, -120, 100);

    // Setup
    button.setup();

    motorA.setup();
    motorB.setup();

    sensor.setup();
    sensor.calibrate();
}

void loop() {

    uint16_t position = sensor.getQTRSensor()->readLineBlack(sensorValues);
    stateMachine.state(position, button.readState());
}