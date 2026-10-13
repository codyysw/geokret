#include "WebTuner.hpp"
#include <WiFi.h>
#include <WebServer.h>


WebTuner::WebTuner(int port) : server(port)
{

}

void WebTuner::setup()
{
    WiFi.softAP(SSID, PASS);
    Serial.print("AP IP: ");
    Serial.println(WiFi.softAPIP());   // usually 192.168.4.1

    server.on("/", [this]() { handleRoot(); });
    server.begin();
}

void WebTuner::tick()
{
    server.handleClient();
}

void WebTuner::handleRoot()
{
    server.send_P(200, "text/html", INDEX_HTML);
}