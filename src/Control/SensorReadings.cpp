//
// Created by Herman Hårstad Gran on 16/04/2024.
//

#include "Control/SensorReadings.hpp"

// Constructor for SensorReadings class
SensorReadings::SensorReadings(int capacity_) : capacity(capacity_), head(0), size(0) {
    buffer = new int[capacity_];
}

// Function for adding values to the array
void SensorReadings::add(int value_) {
    buffer[head] = value_;
    head = (head + 1) % capacity;
    if (size < capacity) {
        size++;
    }
}

// Function for calculating the average value of the array
int SensorReadings::getAverage() const {
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += buffer[i];
    }

    int average = total / size;

    return average;
}