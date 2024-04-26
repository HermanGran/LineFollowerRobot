//
// Created by Herman Hårstad Gran on 26/04/2024.
//

#ifndef LINEFOLLOWERROBOT_WIFI_HPP
#define LINEFOLLOWERROBOT_WIFI_HPP

#include <WiFi.h>
#include "PID/PID.hpp"
#include "Control/Button.hpp"
#include "Control/StateMachine.hpp"

/**
 * The class RobotServer creates a web server used for calibrating PID values and speed for testing
 */
class RobotServer {
public:
    /**
     * Constructor for RobotServer and takes in a instance of PID and StateMachine for updating valeus
     * @param ssid_ Name of the WiFi
     * @param password_ Password of the WiFi
     * @param pid_ Instance of PID class
     * @param stateMachine Instance of StateMachine class
     */
    RobotServer(const char* ssid_, const char* password_, PID &pid_, StateMachine &stateMachine);

    /**
     * Setup function in setup for connecting to WiFi
     */
    void setup();

    /**
     * Update function placed in main loop for checking updates from web server
     */
    void update();

    void sendCoordinate(float x, float y);

private:
    const char* ssid;
    const char* password;

    unsigned long previousTime = 0;
    unsigned long currentTime = millis();

    const long timeoutTime;

    WiFiServer *server;

    PID &pid;
    StateMachine &stateMachine;

    String header;

    float kP, kI, kD;
    int speed;

    void displayWebPage(WiFiClient &client);
    void displayNewWebPage(WiFiClient &client);

    void displayPIDControl(WiFiClient &client);

    void displayOnOffButtons(WiFiClient &client);

    void displayMotorSpeedControls(WiFiClient &client);

    void updatePID(String parameters);

    void handlePIDUpdate(const String &line);
    void updatePIDComponent(const String &line, char component);
    void sendHTTPHeaders(WiFiClient &client);
    void updateSpeed(const String &line, int motor);
};

#endif //LINEFOLLOWERROBOT_WIFI_HPP
