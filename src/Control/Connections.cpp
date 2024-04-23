//
// Created by Herman Hårstad Gran on 23/04/2024.
//

#include "Control/Connections.hpp"

Connections::Connections(PID &pid) : pid(pid), pValue(pid.getPValue()), iValue(pid.getIValue()), dValue(pid.getDValue()) {
    positionService = new BLEService("12345678-1234-5678-1234-56789abcdef0");
    positionCharacteristic = new BLEStringCharacteristic("87654321-4321-8765-4321-fedcba987654", BLERead | BLENotify, 30);

    pidService = new BLEService("12345678-1234-5678-1234-56789abcdef1");
    pCharacteristic = new BLEFloatCharacteristic("abcd1234-ab12-ab12-ab12-abcdef123456", BLERead | BLEWrite);
    iCharacteristic = new BLEFloatCharacteristic("abcd1235-ab12-ab12-ab12-abcdef123457", BLERead | BLEWrite);
    dCharacteristic = new BLEFloatCharacteristic("abcd1236-ab12-ab12-ab12-abcdef123458", BLERead | BLEWrite);

}

void Connections::setup() {
    if (!BLE.begin()) {
        Serial.println("Starting BLE failed");
        while(1);
    }

    BLE.setLocalName("LineFollowerRobot Group 5");
    BLE.setAdvertisedService(*positionService);
    positionService->addCharacteristic(*positionCharacteristic);
    BLE.addService(*positionService);
    positionCharacteristic->writeValue("x:0.00,y:0.00"); // Default value

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

void Connections::updatePosition(float x, float y, float theta) {
    BLEDevice central = BLE.central();

    if (central) {
        String position = ("x: " + String(x, 2) + " , y: " + String(y, 2) + " , theta: " + String(theta, 2)); // Get the current position as a string
        positionCharacteristic->writeValue(position);
    }

}

void Connections::updatePID() {
    if (pCharacteristic->written() or iCharacteristic->written() or dCharacteristic->written()) {
        pid.setPID(pCharacteristic->value(), iCharacteristic->value(), dCharacteristic->value());
        pCharacteristic->writeValue(pValue);
        iCharacteristic->writeValue(iValue);
        dCharacteristic->writeValue(dValue);
    }
}