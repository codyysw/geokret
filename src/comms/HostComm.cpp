#include <cstring>

#include "HostComm.hpp"

HostComm::HostComm(ILink& link_) : link{link_}
{

}

void HostComm::begin()
{
    link.begin();
}

void HostComm::update()
{
    if (!link.isUp()) {
        scanCount = 0;
        return;
    }
    if (scanCount < MAX_POINTS) {
        return;
    }
    flushScan();
}

void HostComm::queueScan(const Packets::ScanPoint& packet)
{
    if (scanCount >= MAX_POINTS) {
        return;
    }
    std::size_t scanPointSize = sizeof(Packets::ScanPoint);
    //scanBuf[scanCount * scanPointSize] = packet;
        std::memcpy(
        scanBuf + scanCount * scanPointSize,
        &packet,
        scanPointSize
    );
    ++scanCount;
}

void HostComm::flushScan()
{
    if (!link.isUp()) {
        return;
    }
    if (scanCount == 0) {
        return;
    }
    link.send(scanBuf, scanCount * sizeof(Packets::ScanPoint));
    scanCount = 0;
}