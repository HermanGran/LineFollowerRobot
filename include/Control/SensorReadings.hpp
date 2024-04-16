//
// Created by Herman Hårstad Gran on 16/04/2024.
//

#ifndef LINEFOLLOWERROBOT_SENSORREADINGS_HPP
#define LINEFOLLOWERROBOT_SENSORREADINGS_HPP

#include <iostream>

/**
 * SensorReadings class, used for saving sensor readings in an array
 */
class SensorReadings {
public:
    /**
     * Constructor for SensorReadings class
     * @param capacity_ Max size for array
     */
    SensorReadings(int capacity_);

    /**
     * Function for adding value to array
     * @param value_
     */
    void add(int value_);

    /**
     * Destructor for SensorReadings class
     */
    ~SensorReadings() {
        delete[] buffer;
    }

    /**
     * Function for getting the average value of all sensor readings
     * @return The average
     */
    int getAverage() const;

private:
    int* buffer;
    int capacity;
    int head;
    int size;
};

#endif //LINEFOLLOWERROBOT_SENSORREADINGS_HPP
