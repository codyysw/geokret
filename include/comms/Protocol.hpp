#pragma once

#include <cstdint>

namespace Packets
{

struct __attribute__((packed)) ScanPoint {
    uint16_t angle;
    uint16_t distCm;
    uint16_t signal;
    uint32_t tMs;
};

struct __attribute__((packed)) Command {
    int16_t  left;        // -1000..1000 (permille)
    int16_t  right;
    uint8_t  turretMode;  // 0 = no request (ignored at first)
    int16_t  turretArg;
};

} // namespace Packets