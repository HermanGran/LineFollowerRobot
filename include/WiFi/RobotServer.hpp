//
// Created by Herman Hårstad Gran on 26/04/2024.
//

#ifndef LINEFOLLOWERROBOT_WIFI_HPP
#define LINEFOLLOWERROBOT_WIFI_HPP

#include <WiFi.h>
#include "PID/PID.hpp"
#include "Control/Button.hpp"

class RobotServer {
public:

    RobotServer(const char* ssid_, const char* password_, PID &pid_);

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

    String header;

    float kP, kI, kD;

    void displayWebPage(WiFiClient &client);

    void displayButtons(WiFiClient &client);

    void updatePID(String parameters);
};

#endif //LINEFOLLOWERROBOT_WIFI_HPP
