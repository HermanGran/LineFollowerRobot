//
// Created by Herman Hårstad Gran on 22/04/2024.
//

#include "Motor/Encoder.hpp"

Encoder* Encoder::instances[2] = {nullptr, nullptr};

Encoder::Encoder(int pinA, int pinB) : inputA(pinA), inputB(pinB), encoderCount(0), prevEncoderCount(0) {
    if (instances[0] == nullptr) {
        instances[0] = this;
    } else {
        instances[1] = this;
    }
}

void Encoder::begin() {
    pinMode(inputA, INPUT);
    pinMode(inputB, INPUT);
    attachInterrupt(digitalPinToInterrupt(inputA), handleInterruptA, RISING);
    //attachInterrupt(digitalPinToInterrupt(inputB), handleInterruptB, CHANGE);
}

void Encoder::handleInterruptA() {
    for (int i = 0; i < 2; ++i) {
        if (Encoder::instances[i] != nullptr && digitalRead(Encoder::instances[i]->inputA) > digitalRead(Encoder::instances[i]->inputB)) {
            Encoder::instances[i]->encoderCount++;
        }
    }
}

void Encoder::handleInterruptB() {
    for (int i = 0; i < 2; ++i) {
        if (Encoder::instances[i] != nullptr && digitalRead(Encoder::instances[i]->inputA) < digitalRead(Encoder::instances[i]->inputB)) {
            Encoder::instances[i]->encoderCount--;
        }
    }
}

long Encoder::getEncoderCount() const {
    return encoderCount;
}

void Encoder::resetEncoderCount() {
    encoderCount = 0;
}

float Encoder::getDeltaEncoderCount() {
    float deltaEncoderCount = encoderCount - prevEncoderCount;
    prevEncoderCount = encoderCount;
    return deltaEncoderCount;
}