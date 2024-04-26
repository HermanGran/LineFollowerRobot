//
// Created by Herman Hårstad Gran on 22/04/2024.
//

#ifndef LINEFOLLOWERROBOT_ROBOTODOMETRY_HPP
#define LINEFOLLOWERROBOT_ROBOTODOMETRY_HPP

#include <cmath>
#include <utility>
#include <vector>
#include "Arduino.h"

/**
 * RobotOdometry is used for calculating the position and orientation of the robot with the encoders
 */
class RobotOdometry {
public:

    /**
     * Constructor
     * @param wheelBase Distance between wheels
     */
    RobotOdometry(float wheelBase);

    /**
     * Calculates and updates the position from number of rotation from the encoders
     * @param dL Encoder from left wheel
     * @param dR Encoder from right wheel
     */
    void update(float dL, float dR);

    /**
     * Retrieving latest coordinate
     * @return X coordinate
     */
    float getX() const;

    /**
     * Retrieving latest coordinate
     * @return Y coordinate
     */
    float getY() const;

    /**
     * Retrieves latest orientation
     * @return Angle of orientation from start position
     */
    float getTheta() const;

    /**
     * Logs the position in an vector to map the path robot drives
     * @param x Current x coordinate
     * @param y Current y coordinate
     */
    void logPosition(float x, float y);

    /**
     * Checks current distance from origin
     * @param x Current x position
     * @param y Current y position
     * @param threshold How close the robot needs to be to the origin
     * @return False until close enough to origin
     */
    bool checkLapCompletion(float x, float y, float threshold = 1.0);

    /**
     * Retrieves vector that contains the path
     * @return Vector pair of x and y coordinates
     */
    std::vector<std::pair<float, float>> getPath();

private:
    float x, y, theta, wheelbase;
    std::vector<std::pair<float, float>> path;
};

#endif //LINEFOLLOWERROBOT_ROBOTODOMETRY_HPP
