#include "UdpLink.hpp"
#include "Secrets.hpp"

void UdpLink::begin()
{
    WiFi.setSleep(false);
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
        udp.stop();
        udpStarted = false;
        return;
    }
    if (!udpStarted) {
        udp.begin(Connection::UDP_PORT);
    }
    udp.write(msg, len);
    udp.endPacket();
}