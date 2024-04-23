//
// Created by Herman Hårstad Gran on 22/04/2024.
//

#include "Control/RobotOdometry.hpp"

RobotOdometry::RobotOdometry(float wheelBase_) : x(0.0), y(0.0), theta(0), wheelbase(wheelBase_) {}

void RobotOdometry::update(float dL_, float dR_) {
    float dL = (float(dL_) / 30.0) * M_PI * 2.9;
    float dR = (float(dR_) / 30.0) * M_PI * 2.9;

    float deltaTheta = (dR - dL) / wheelbase;
    float R = 0;

    if (deltaTheta != 0) {
        float dC = (dL + dR) / 2;
        R = dC / deltaTheta;
        float newTheta = theta + deltaTheta;
        x += R * (sin(newTheta) - sin(theta));
        y += R * (cos(newTheta) - cos(theta));
        theta = fmod(newTheta, 2 * M_PI);
    } else {
        x += dL * cos(theta);
        y += dL * sin(theta);

    }

    Serial.print("x: ");
    Serial.print(x);
    Serial.print("    y: ");
    Serial.print(y);
    Serial.print("    Theta: ");
    Serial.print(degrees(theta));
    Serial.print("     ");
}

float RobotOdometry::getX() const {
    return x;
}

float RobotOdometry::getY() const {
    return y;
}

float RobotOdometry::getTheta() const {
    return theta;
}

void RobotOdometry::logPosition(float x, float y) {
    path.emplace_back(x, y);
}

bool RobotOdometry::checkLapCompletion(float x, float y, float threshold) {
    float startX = path.front().first;
    float startY = path.front().second;
    float distance = sqrt((x - startX) * (x - startX) + (y - startY) * (y - startY));

    Serial.print(distance);

    return distance <= threshold;
}

std::vector<std::pair<float, float>> RobotOdometry::getPath() {
    return path;
}