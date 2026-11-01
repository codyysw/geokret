#pragma once

constexpr int DELAY = 25;

struct EnginePins {
    const int pwm;
    const int in1;
    const int in2;
};

struct Lidar1DPins {
    const int RXD; // Receiving/Data
    const int TXD; // Transmitting/Clock
};


namespace Pins {
    constexpr EnginePins FRONT_RIGHT  {32, 33, 25};
    constexpr EnginePins REAR_LEFT   {23, 22, 21};
    constexpr EnginePins FRONT_LEFT {17, 18, 16};
    constexpr EnginePins REAR_RIGHT  {26, 14, 27};
    constexpr Lidar1DPins Lidar1D {35,-1};
}