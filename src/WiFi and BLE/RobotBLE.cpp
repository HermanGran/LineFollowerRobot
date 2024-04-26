//
// Created by Herman Hårstad Gran on 23/04/2024.
//

#include "WiFi and BLE/RobotBLE.hpp"

// Constructor
RobotBLE::RobotBLE(PID &pid) : pid(pid), pValue(pid.getPValue()), iValue(pid.getIValue()), dValue(pid.getDValue()), update(0) {
    // Creates a position service with UUID
    positionService = new BLEService("12345678-1234-5678-1234-56789abcdef0");
    positionCharacteristic = new BLEStringCharacteristic("87654321-4321-8765-4321-fedcba987654", BLERead | BLENotify, 40);

    // Creates a PID service with UUID
    pidService = new BLEService("12345678-1234-5678-1234-56789abcdef1");
    pCharacteristic = new BLEFloatCharacteristic("abcd1234-ab12-ab12-ab12-abcdef123456", BLERead | BLEWrite);
    iCharacteristic = new BLEFloatCharacteristic("abcd1235-ab12-ab12-ab12-abcdef123457", BLERead | BLEWrite);
    dCharacteristic = new BLEFloatCharacteristic("abcd1236-ab12-ab12-ab12-abcdef123458", BLERead | BLEWrite);

}

// Initializes RobotBLE class
void RobotBLE::setup() {
    if (!BLE.begin()) {
        Serial.println("Starting BLE failed");
        while(1);
    }

    // Sets name of BLE signal
    BLE.setLocalName("LineFollowerRobot Group 5");

    // Initializes position service
    BLE.setAdvertisedService(*positionService);
    positionService->addCharacteristic(*positionCharacteristic);
    BLE.addService(*positionService);
    positionCharacteristic->writeValue("x:0.00,y:0.00"); // Default value

    // Initializes PID service
    BLE.setAdvertisedService(*pidService);
    pidService->addCharacteristic(*pCharacteristic);
    pidService->addCharacteristic(*iCharacteristic);
    pidService->addCharacteristic(*dCharacteristic);
    pCharacteristic->writeValue(pValue);
    iCharacteristic->writeValue(iValue);
    dCharacteristic->writeValue(dValue);
    BLE.addService(*pidService);
    BLE.advertise();

    Serial.println("BLE device is now active, waiting for connections...");
}

// Sends the updated position to BLE device
void RobotBLE::updatePosition(float x, float y, float theta) {
    BLEDevice central = BLE.central();

    if ((central) && (update == 40)) {
        update = 0;
        String position = ("x: " + String(x, 2) + " , y: " + String(y, 2) + " , theta: " + String(theta, 5)); // Get the current position as a string
        positionCharacteristic->writeValue(position);
    } else {
        ++update;
    }
}

// Reads updated value from BLE to update pid
void RobotBLE::updatePID() {
    if (pCharacteristic->written() or iCharacteristic->written() or dCharacteristic->written()) {
        pid.setPID(pCharacteristic->value(), iCharacteristic->value(), dCharacteristic->value());
        pCharacteristic->writeValue(pValue);
        iCharacteristic->writeValue(iValue);
        dCharacteristic->writeValue(dValue);
    }
}