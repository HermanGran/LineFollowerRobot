//
// Created by Herman Hårstad Gran on 16/04/2024.
//

#include "Control/SensorReadings.hpp"

SensorReadings::SensorReadings(int capacity_) : capacity(capacity_), head(0), size(0) {
    buffer = new int[capacity_];
}

void SensorReadings::add(int value_) {
    buffer[head] = value_;
    head = (head + 1) % capacity;
    if (size < capacity) {
        size++;
    }
}

int SensorReadings::getAverage() const {
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += buffer[i];
    }

    int average = total / size;

    return average;
}