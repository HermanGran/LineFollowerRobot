//
// Created by Herman Hårstad Gran on 22/04/2024.
//

#ifndef LINEFOLLOWERROBOT_ROBOTODEMETRY_HPP
#define LINEFOLLOWERROBOT_ROBOTODEMETRY_HPP

#include <cmath>
#include <utility>
#include <vector>
#include "Arduino.h"

class RobotOdemetry {
public:
    RobotOdemetry(float wheelBase);

    void update(float dL, float dR);

    float getX() const;
    float getY() const;
    float getTheta() const;

    void logPosition(float x, float y);

    bool checkLapCompletion(float x, float y, float threshold = 1.0);

    std::vector<std::pair<float, float>> getPath();
private:
    float x, y, theta, wheelbase;

    std::vector<std::pair<float, float>> path;
};

#endif //LINEFOLLOWERROBOT_ROBOTODEMETRY_HPP
