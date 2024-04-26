//
// Created by Herman Hårstad Gran on 26/04/2024.
//

#include "WiFi and BLE/RobotServer.hpp"

RobotServer::RobotServer(const char* ssid_, const char* password_, PID &pid, StateMachine &stateMachine) : ssid(ssid_), password(password_), timeoutTime(2000), pid(pid), stateMachine(stateMachine) {
    server = new WiFiServer(80);
}

void RobotServer::setup() {
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
        Serial.println("New client connected.");
        String currentLine = ""; // to store the line from the client
        currentTime = millis();  // reset the current time

        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                Serial.write(c);
                header += c;
                if (c == '\n') {  // end of line
                    if (currentLine.length() == 0) {  // if the line is empty, it means the HTTP request end
                        sendHTTPHeaders(client);
                        handlePIDUpdate(header);
                        displayWebPage(client);
                        displayOnOffButtons(client, header);
                        displayPIDControl(client);
                        displayMotorSpeedControls(client);


                        client.println("</body></html>");
                        Serial.println();
                        break;
                    } else {  // process the current line
                        currentLine = ""; // reset current line
                    }
                } else if (c != '\r') {
                    currentLine += c;  // add character to line
                }
            }
        }
        header = "";

        client.stop();
        Serial.println("Client disconnected.");
        Serial.println("");
    }
}

void RobotServer::handlePIDUpdate(const String &line) {
    if (line.startsWith("GET /updateP")) {
        updatePIDComponent(line, 'P');
    } else if (line.startsWith("GET /updateI")) {
        updatePIDComponent(line, 'I');
    } else if (line.startsWith("GET /updateD")) {
        updatePIDComponent(line, 'D');
    } else if (line.startsWith("GET /updateSpeed")) {
        updateSpeed(line, 1);
    } else if (line.startsWith("GET /updateLeftTurnMotorA")) {
        updateSpeed(line, 2);
    } else if (line.startsWith("GET /updateRightTurnMotorA")) {
        updateSpeed(line, 3);
    } else if (line.startsWith("GET /updateLeftTurnMotorB")) {
        updateSpeed(line, 4);
    } else if (line.startsWith("GET /updateRightTurnMotorB")) {
        updateSpeed(line, 5);
    }
}

void RobotServer::updatePIDComponent(const String &line, char component) {

    int start = line.indexOf('=') + 1;
    int end = line.indexOf(' ', start);

    String valueStr = line.substring(start, end);
    float value = valueStr.toFloat();

    // Update the appropriate component
    switch (component) {
        case 'P':
            pid.setPValue(value);
            break;
        case 'I':
            pid.setIValue(value);
            break;
        case 'D':
            pid.setDValue(value);
            break;
    }
}

void RobotServer::updateSpeed(const String &line, int motor) {

    int start = line.indexOf('=') + 1;
    int end = line.indexOf(' ', start);

    String valueStr = line.substring(start, end);
    float value = valueStr.toFloat();

    pid.setMotorSpeed(value);

    switch (motor) {
        case 1:
            pid.setMotorSpeed(value);
            break;
        case 2:
            stateMachine.setLeftTurnSpeedMotorA(value);
            break;
        case 3:
            stateMachine.setRightTurnSpeedMotorA(value);
            break;
        case 4:
            stateMachine.setLeftTurnSpeedMotorB(value);
            break;
        case 5:
            stateMachine.setRightTurnSpeedMotorB(value);
            break;
    }
}

void RobotServer::sendHTTPHeaders(WiFiClient &client) {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println("Connection: close");
    client.println();
}


void RobotServer::displayWebPage(WiFiClient &client) {
    // Display the HTML web page
    client.println("<!DOCTYPE html><html>");
    client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    client.println("<link rel=\"icon\" href=\"data:,\">");
    // CSS to style the on/off buttons
    // Feel free to change the background-color and font-size attributes to fit your preferences
    client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
    client.println(".button {\n"
                   "  background-color: #04AA6D;\n"
                   "  border: none;\n"
                   "  color: white;\n"
                   "  padding: 15px 32px;\n"
                   "  text-align: center;\n"
                   "  text-decoration: none;\n"
                   "  display: inline-block;\n"
                   "  font-size: 16px;\n"
                   "}");
    client.println(".button2 {\n"
                   "  background-color: #f44336;\n"
                   "  border: none;\n"
                   "  color: white;\n"
                   "  padding: 15px 32px;\n"
                   "  text-align: center;\n"
                   "  text-decoration: none;\n"
                   "  display: inline-block;\n"
                   "  font-size: 16px;\n"
                   "}");
    client.println("</style></head>");

    // Web Page Heading
    client.println("<body><h1>LineFollowerRobot</h1>");
}

void RobotServer::displayPIDControl(WiFiClient &client) {
    client.println("<h2>Update PID Values</h2>");

// Display current PID values
    client.println("<p>Current PID Values:</p>");
    client.println("<ul>");
    client.println("<li><strong>Proportional (P):</strong> " + String(pid.getPValue()) + "</li>");
    client.println("<li><strong>Integral (I):</strong> " + String(pid.getIValue()) + "</li>");
    client.println("<li><strong>Derivative (D):</strong> " + String(pid.getDValue()) + "</li>");
    client.println("</ul>");

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

void RobotServer::displayMotorSpeedControls(WiFiClient &client) {
    // Motor speed Value

    client.println("<h2>Speed control</h2>");
    client.println("<ul>");
    client.println("<li><strong>Current speed:</strong> " + String(pid.getMaxSpeed()) + "</li>");
    client.println("</ul>");

    client.println("<form action=\"/updateSpeed\" method=\"GET\">");
    client.println("<label for=\"Speed\">Speed: </label><br>");
    client.println("<input type=\"text\" id=\"Speed\" name=\"Motor speed\" value=\"" + String(speed) + "\"><br>");
    client.println("<input type=\"submit\" value=\"Update Speed\">");
    client.println("</form>");

    // Left Turn speed
    client.println("<h2>Left turn</h2>");
    client.println("<p>Current speeds:</p>");
    client.println("<ul>");
    client.println("<li><strong>Motor A:</strong> " + String(stateMachine.getLeftTurnSpeedMotorA()) + "</li>");
    client.println("<li><strong>Motor B:</strong> " + String(stateMachine.getLeftTurnSpeedMotorB()) + "</li>");
    client.println("</ul>");

    client.println("<form action=\"/updateLeftTurnMotorA\" method=\"GET\">");
    client.println("<label for=\"Speed\">Motor A: </label><br>");
    client.println("<input type=\"text\" id=\"SpeedL MotorA\" name=\"Motor A left turn\" value=\"" + String(speed) + "\"><br>");
    client.println("<input type=\"submit\" value=\"Update Speed\">");
    client.println("</form>");

    client.println("<form action=\"/updateLeftTurnMotorB\" method=\"GET\">");
    client.println("<label for=\"Speed\">Motor B: </label><br>");
    client.println("<input type=\"text\" id=\"SpeedL MotorB\" name=\"Motor B left turn\" value=\"" + String(speed) + "\"><br>");
    client.println("<input type=\"submit\" value=\"Update Speed\">");
    client.println("</form>");

    client.println("<h2>Right turn</h2>");
    client.println("<p>Current speeds:</p>");
    client.println("<ul>");
    client.println("<li><strong>Motor A:</strong> " + String(stateMachine.getRightTurnSpeedMotorA()) + "</li>");
    client.println("<li><strong>Motor B:</strong> " + String(stateMachine.getRightTurnSpeedMotorB()) + "</li>");
    client.println("</ul>");

    client.println("<form action=\"/updateRightTurnMotorA\" method=\"GET\">");
    client.println("<label for=\"Speed\">Motor A: </label><br>");
    client.println("<input type=\"text\" id=\"SpeedR MotorA\" name=\"Motor A right turn\" value=\"" + String(speed) + "\"><br>");
    client.println("<input type=\"submit\" value=\"Update Speed\">");
    client.println("</form>");

    client.println("<form action=\"/updateRightTurnMotorB\" method=\"GET\">");
    client.println("<label for=\"Speed\">Motor B: </label><br>");
    client.println("<input type=\"text\" id=\"SpeedR MotorB\" name=\"Motor B right turn\" value=\"" + String(speed) + "\"><br>");
    client.println("<input type=\"submit\" value=\"Update Speed\">");
    client.println("</form>");
}

void RobotServer::sendCoordinate(float x, float y) {
    WiFiClient client = server->available();

    if (client.available()) {
        client.printf("");
    }
}

void RobotServer::displayNewWebPage(WiFiClient &client) {
    client.println(R"rawliteral(
<!DOCTYPE html>
<html lang="en"
<head>
<meta charset="UTF-8">
<title>Turn Configuration</title>
)rawliteral");
}

void RobotServer::displayOnOffButtons(WiFiClient &client, const String &line) {
    // Determine the action based on the received URL path
    if (line.startsWith("GET /Robot/on")) {
        stateMachine.getButton().setToggleState(true);
    } else if (line.startsWith("GET /Robot/off")) {
        stateMachine.getButton().setToggleState(false);
    }

    if (line.startsWith("GET /turnFunction/on")) {
        stateMachine.setTurnFunctionState(true);
    } else if (line.startsWith("GET /turnFunction/off")) {
        stateMachine.setTurnFunctionState(false); // Corrected to set state to false
    }

    // Dynamically display buttons based on the current state
    client.println("<p>Robot Power:</p>");
    if (stateMachine.getButton().readState()) {
        client.println("<p><a href=\"/Robot/off\"><button class=\"button button2\">Turn OFF</button></a></p>");
    } else {
        client.println("<p><a href=\"/Robot/on\"><button class=\"button\">Turn ON</button></a></p>");
    }

    client.println("<p>Turn Function:</p>");
    if (stateMachine.getTurnFunctionState()) {
        client.println("<p><a href=\"/turnFunction/off\"><button class=\"button button2\">Turn OFF</button></a></p>");
    } else {
        client.println("<p><a href=\"/turnFunction/on\"><button class=\"button\">Turn ON</button></a></p>");
    }
}