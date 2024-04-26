//
// Created by Herman Hårstad Gran on 22/04/2024.
//

#include "Motor/Encoder.hpp"

Encoder* Encoder::instanceA = nullptr;
Encoder* Encoder::instanceB = nullptr;

Encoder::Encoder(int pinA_, int pinB_)
: pinA(pinA_), pinB(pinB_), encoderCountA(0), prevEncoderCountA(0), encoderCountB(0), prevEncoderCountB(0) {}


void Encoder::setup() {
    pinMode(pinA, INPUT);
    pinMode(pinB, INPUT);
    attachInterrupt(digitalPinToInterrupt(pinA), isrHandlerA, RISING);
    attachInterrupt(digitalPinToInterrupt(pinA), isrHandlerB, RISING);
}

void Encoder::isrHandlerA() {
    instanceA->handleInterruptA();
}

void Encoder::isrHandlerB() {
    instanceB->handleInterruptB();
}

void Encoder::handleInterruptA() {
    if (digitalRead(instanceA->pinA) > digitalRead(instanceA->pinB)) {
        instanceA->encoderCountA++;
    } else {
        instanceA->encoderCountA--;
    }
}

void Encoder::handleInterruptB() {
    if (digitalRead(instanceB->pinA) > digitalRead(instanceB->pinB)) {
        instanceB->encoderCountB++;
    } else {
        instanceB->encoderCountB--;
    }
}

long Encoder::getEncoderCountA() const {
    return encoderCountA;
}

long Encoder::getEncoderCountB() const {
    return encoderCountB;
}

void Encoder::resetEncoderCountA() {
    encoderCountA = 0;
}

void Encoder::resetEncoderCountB() {
    encoderCountB = 0;
}

float Encoder::getDeltaEncoderCountA() {
    float deltaEncoderCount = encoderCountA - prevEncoderCountA;
    prevEncoderCountA = encoderCountA;
    return deltaEncoderCount;
}

float Encoder::getDeltaEncoderCountB() {
    float deltaEncoderCount = encoderCountB- prevEncoderCountB;
    prevEncoderCountB = encoderCountB;
    return deltaEncoderCount;
}