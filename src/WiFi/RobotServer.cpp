//
// Created by Herman Hårstad Gran on 26/04/2024.
//

#include "WiFi/RobotServer.hpp"

RobotServer::RobotServer(const char* ssid_, const char* password_, PID &pid) : ssid(ssid_), password(password_), timeoutTime(2000), pid(pid) {
    server = new WiFiServer(80);
}

void RobotServer::connect() {
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    server->begin();
}

void RobotServer::update() {
    WiFiClient client = server->available();

    if (client) {
        currentTime = millis();
        previousTime = currentTime;
        Serial.println("New client.");
        String currentLine = "";
        while (client.connected() && currentTime - previousTime <= timeoutTime) {
            currentTime = millis();
            if(client.available()) {
                char c = client.read();
                Serial.write(c);
                header += c;
                if (c == '\n') {
                    if (currentLine.length() == 0) {
                        client.println("HTTP/1.1 200 ok");
                        client.println("Content-type:text/html");
                        client.println("Connection: close");
                        client.println();

                        displayWebPage(client);

                        displayButtons(client);

                        if (header.startsWith("GET /updateP")) {
                            Serial.println("P");
                        }
                        if (currentLine.startsWith("GET /updateI")) {
                            Serial.println("I");
                        }
                        if (currentLine.startsWith("GET /updateD")) {
                            Serial.println("D");
                        }

                        break;
                    } else {
                        currentLine = "";
                    }
                } else if (c != '\r'){
                    currentLine += c;
                }
            }
        }

        header = "";

        client.stop();
        Serial.println("Client disconnected.");
        Serial.println("");
    }
}

void RobotServer::displayWebPage(WiFiClient &client) {
    // Display the HTML web page
    client.println("<!DOCTYPE html><html>");
    client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    client.println("<link rel=\"icon\" href=\"data:,\">");
    // CSS to style the on/off buttons
    // Feel free to change the background-color and font-size attributes to fit your preferences
    client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
    client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
    client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
    client.println(".button2 {background-color: #555555;}</style></head>");

    // Web Page Heading
    client.println("<body><h1>ESP32 Web Server</h1>");
}

void RobotServer::displayButtons(WiFiClient &client) {
    client.println("<h2>Update PID Values</h2>");

// Display current PID values
    client.println("<p>Current PID Values:</p>");
    client.println("<ul>");
    client.println("<li>Proportional (P): " + String(kP) + "</li>");
    client.println("<li>Integral (I): " + String(kI) + "</li>");
    client.println("<li>Derivative (D): " + String(kD) + "</li>");
    client.println("</ul>");

// Form to submit new PID values
    /*
    client.println("<form action=\"/updatePID\" method=\"GET\">");
    client.println("<label for=\"P\">P (Proportional):</label><br>");
    client.println("<input type=\"text\" id=\"P\" name=\"P\" value=\"" + String(kP) + "\"><br>");
    client.println("<label for=\"I\">I (Integral):</label><br>");
    client.println("<input type=\"text\" id=\"I\" name=\"I\" value=\"" + String(kI) + "\"><br>");
    client.println("<label for=\"D\">D (Derivative):</label><br>");
    client.println("<input type=\"text\" id=\"D\" name=\"D\" value=\"" + String(kD) + "\"><br>");
    client.println("<input type=\"submit\" value=\"Update PID\">");
    client.println("</form>");
    */
    // P Value
    client.println("<form action=\"/updateP\" method=\"GET\">");
    client.println("<label for=\"P\">P (Proportional):</label><br>");
    client.println("<input type=\"text\" id=\"P\" name=\"P\" value=\"" + String(kP) + "\"><br>");
    client.println("<input type=\"submit\" value=\"Update P\">");
    client.println("</form>");

    // I Value
    client.println("<form action=\"/updateI\" method=\"GET\">");
    client.println("<label for=\"I\">I (Integral):</label><br>");
    client.println("<input type=\"text\" id=\"I\" name=\"I\" value=\"" + String(kI) + "\"><br>");
    client.println("<input type=\"submit\" value=\"Update I\">");
    client.println("</form>");

    // P Value
    client.println("<form action=\"/updateD\" method=\"GET\">");
    client.println("<label for=\"D\">D (Derrivetive):</label><br>");
    client.println("<input type=\"text\" id=\"D\" name=\"D\" value=\"" + String(kD) + "\"><br>");
    client.println("<input type=\"submit\" value=\"Update D\">");
    client.println("</form>");


}