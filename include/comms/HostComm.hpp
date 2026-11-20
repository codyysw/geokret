#pragma once

#include "ILink.hpp"
#include "Protocol.hpp"

class HostComm
{
public: // CONFIGURABLE CONSTANS
    static constexpr std::size_t MAX_POINTS = 20;
public:
    explicit HostComm(ILink& link_);
    void begin();
    void update();
    void queueScan(const Packets::ScanPoint& packet);
private:
    void flushScan();

    ILink& link;
    uint8_t scanBuf[MAX_POINTS * sizeof(Packets::ScanPoint)];
    std::size_t scanCount = 0;
};