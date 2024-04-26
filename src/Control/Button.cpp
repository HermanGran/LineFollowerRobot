//
// Created by Herman Hårstad Gran on 26/04/2024.
//

#include "Control/Button.hpp"

// Constructor for button class
Button::Button(const int buttonPin_, unsigned long debounceDuration_) : buttonPin(buttonPin_), debounceDuration(debounceDuration_), lastButtonState(false), lastTimeButtonStateChanged(0) {}

// To initialize the button
void Button::setup() {
    pinMode(buttonPin, INPUT_PULLUP);
}

// Function for setting toggleState true or false with the button
bool Button::readState() {
    int currentButtonState = digitalRead(buttonPin);
    unsigned long currentTime = millis();

    // Check for state change and if it's been long enough since the last change for debounce
    if (currentButtonState != lastButtonState && (currentTime - lastTimeButtonStateChanged) > debounceDuration) {
        // Update time stamp of state change
        lastTimeButtonStateChanged = currentTime;
        // Update the last known button state
        lastButtonState = currentButtonState;

        // Change the toggle state only if the new button state is LOW
        if (currentButtonState == LOW) {
            toggleState = !toggleState;
        }
    }

    return toggleState;
}

// Function for setting toggleState true or false
void Button::setToggleState(bool toggleState_) {
    toggleState = toggleState_;
}