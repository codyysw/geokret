#include <Arduino.h>
#include <WiFi.h>

#include "UdpLink.hpp"
#include "Secrets.hpp"

void UdpLink::begin()
{
    WiFi.setSleep(WIFI_PS_MIN_MODEM);
    WiFi.begin(Connection::WIFI_SSID, Connection::WIFI_PASSWORD);    
    udpStarted = false;
}

bool UdpLink::isUp() const
{
    return WiFi.status() == WL_CONNECTED;
}

void UdpLink::send(const uint8_t* msg, std::size_t len)
{
    if (!isUp()) {
        Serial.println("WIFI NOT CONNECTED");
        if (udpStarted) {
            udp.stop();
            udpStarted = false;
        }
        return;
    }
    if (!udpStarted) {
        Serial.println("UDP NOT STARTED");
        udp.begin(Connection::UDP_PORT);
        udpStarted = true;
    }
    Serial.println("SENDING A PACKET");
    udp.beginPacket(Connection::HOST_IP, Connection::UDP_PORT);
    udp.write(msg, len);
    udp.endPacket();
}