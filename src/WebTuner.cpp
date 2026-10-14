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
    server.on("/get", [this]() { handleGet(); });
    server.on("/set", [this]() { handleSet(); });
    server.begin();
}

void WebTuner::tick()
{
    server.handleClient();
    print();
}

void WebTuner::handleRoot()
{
    server.send_P(200, "text/html", INDEX_HTML);
}

void WebTuner::handleGet() {
  String json = "{\"acc\":" + String(getAcc(), 2) +
                ",\"dec\":" + String(getDec(), 2) + "}";
  server.send(200, "application/json", json);
}

void WebTuner::handleSet()
{
    if (server.hasArg("acc")) {
        this->setAcc( constrain(server.arg("acc").toFloat(), 0.1f, 50.0f) );
    }
    if (server.hasArg("dec")) {
        this->setDec( constrain(server.arg("dec").toFloat(), 0.1f, 50.0f) );
    }
    server.send(200, "text/plain", "OK");
}

void WebTuner::print() const
{
    Serial.printf("[TUNER] acc = %.1f, dec = %.1f\n", getAcc(), getDec());
}