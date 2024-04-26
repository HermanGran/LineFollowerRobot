//
// Created by Herman Hårstad Gran on 26/04/2024.
//

#ifndef LINEFOLLOWERROBOT_BUTTON_HPP
#define LINEFOLLOWERROBOT_BUTTON_HPP

#include <Arduino.h>

/**
 * Class for starting and stopping the robot with a button
 */
class Button {
public:

    /**
     * Constructor for button
     * @param buttonPin Input pin for button
     * @param debounceDuration_ Duration before it can be pressed again
     */
    Button(const int buttonPin, unsigned long debounceDuration_);

    /**
     * Setup function for initializing
     */
    void setup();

    /**
     * Function for setting the state true or false
     * @return True or false
     */
    bool readState();

    /**
     * To set the the state true or false
     * @param toggleState_
     */
    void setToggleState(bool toggleState_);

private:
    const int buttonPin;

    int lastButtonState;
    bool toggleState;

    unsigned long debounceDuration;
    unsigned long lastTimeButtonStateChanged;
};

#endif //LINEFOLLOWERROBOT_BUTTON_HPP
