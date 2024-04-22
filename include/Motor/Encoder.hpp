//
// Created by Herman Hårstad Gran on 22/04/2024.
//

#ifndef LINEFOLLOWERROBOT_ENCODER_HPP
#define LINEFOLLOWERROBOT_ENCODER_HPP

#include "Arduino.h"
#include <cmath>

class Encoder {
public:
    Encoder(int pinA, int pinB);

    void begin();

    long getEncoderCount() const;

    void resetEncoderCount();

    float getDeltaEncoderCount();

private:
    int inputA;
    int inputB;
    volatile long encoderCount;
    volatile long prevEncoderCount;

    static Encoder* instances[2];
    static void handleInterruptA();
    static void handleInterruptB();

};

#endif //LINEFOLLOWERROBOT_ENCODER_HPP
