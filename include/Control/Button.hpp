//
// Created by Herman Hårstad Gran on 26/04/2024.
//

#ifndef LINEFOLLOWERROBOT_BUTTON_HPP
#define LINEFOLLOWERROBOT_BUTTON_HPP

#include <Arduino.h>

class Button {
public:

    Button(const int buttonPin, unsigned long debounceDuration_);

    void setup();

    bool readState();

    void setToggleState(bool toggleState_);

private:
    const int buttonPin;

    int lastButtonState;
    bool toggleState;

    unsigned long debounceDuration;
    unsigned long lastTimeButtonStateChanged;
};

#endif //LINEFOLLOWERROBOT_BUTTON_HPP
