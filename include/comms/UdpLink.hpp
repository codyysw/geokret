#pragma once

#include <WiFiUdp.h>
#include <cstdint>
#include "ILink.hpp"

class UdpLink : public ILink
{
public:
    void begin() override;
    bool isUp() const override;
    void send(const uint8_t* msg, std::size_t len) override;
    std::size_t receive(uint8_t* buf, std::size_t maxLen) override { return 0; }
private:
    bool udpStarted = false;
    WiFiUDP udp;
};