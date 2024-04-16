//
// Created by Herman Hårstad Gran on 16/04/2024.
//

#ifndef LINEFOLLOWERROBOT_SENSORREADINGS_HPP
#define LINEFOLLOWERROBOT_SENSORREADINGS_HPP

#include <iostream>

class SensorReadings {
public:
    SensorReadings(int capacity_);

    void add(int value_);

    ~SensorReadings() {
        delete[] buffer;
    }

    int getAverage() const;

private:
    int* buffer;
    int capacity;
    int head;
    int size;
};

#endif //LINEFOLLOWERROBOT_SENSORREADINGS_HPP
