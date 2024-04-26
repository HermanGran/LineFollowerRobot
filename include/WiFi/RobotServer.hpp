//
// Created by Herman Hårstad Gran on 26/04/2024.
//

#ifndef LINEFOLLOWERROBOT_WIFI_HPP
#define LINEFOLLOWERROBOT_WIFI_HPP

#include <WiFi.h>
#include "PID/PID.hpp"
#include "Control/Button.hpp"
#include "Control/StateMachine.hpp"

class RobotServer {
public:

    RobotServer(const char* ssid_, const char* password_, PID &pid_, StateMachine &stateMachine);

    void connect();

    void update();

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

    void displayButtons(WiFiClient &client);

    void displayOnOffButtons(WiFiClient &client, const String &line);

    void updatePID(String parameters);

    void handlePIDUpdate(const String &line);
    void updatePIDComponent(const String &line, char component);
    void sendHTTPHeaders(WiFiClient &client);
    void updateSpeed(const String &line, int motor);
};

#endif //LINEFOLLOWERROBOT_WIFI_HPP
