//
// Created by Herman Hårstad Gran on 22/04/2024.
//

#ifndef LINEFOLLOWERROBOT_ENCODER_HPP
#define LINEFOLLOWERROBOT_ENCODER_HPP

#include "Arduino.h"
#include <cmath>

/**
 * Class for handling motor up to two motor encoder
 */
class Encoder {
public:
    /**
     * Constructor for encoder class
     * @param pinA Input pin for encoder A
     * @param pinB Input pin for encoder B
     */
    Encoder(int pinA, int pinB);

    /**
     * Setup function for encoders
     */
    void setup();

    /**
     * Returns encoder count for instance A
     * @return Encoder count
     */
    long getEncoderCountA() const;

    /**
     * Returns encoder count for instance b
     * @return Encoder count
     */
    long getEncoderCountB() const;

    /**
     * Resets encoder count for instance A
     */
    void resetEncoderCountA();

    /**
     * Resets encoder count for instance B
     */
    void resetEncoderCountB();

    /**
     * Calculates and returns delta encoder count for instance A, number of turns since last measure
     * @return delta encoder count
     */
    float getDeltaEncoderCountA();

    /**
     * Calculates and returns delta encoder count for instance B, number of turns since last measure
     * @return delta encoder count
     */
    float getDeltaEncoderCountB();

    /**
     * Used for handling the need of static functions and variables for encoder A
     */
    static void isrHandlerA();

    /**
     * Used for handling the need of static functions and variables for encoder B
     */
    static void isrHandlerB();

private:
    int pinA, pinB;

    volatile long encoderCountA;
    volatile long prevEncoderCountA;

    volatile long encoderCountB;
    volatile long prevEncoderCountB;

    static void handleInterruptA();
    static void handleInterruptB();

    static Encoder* instanceA;
    static Encoder* instanceB;
};

#endif //LINEFOLLOWERROBOT_ENCODER_HPP
