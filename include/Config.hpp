#pragma once

#include <cstdint>

namespace IntervalsMs {
    constexpr int ENGINE = 25;
    constexpr int SENSOR = 10;
}

struct EnginePins {
    const uint8_t pwm;
    const uint8_t in1;
    const uint8_t in2;
};

struct StepperPins {
    const uint8_t IN1;
    const uint8_t IN2;
    const uint8_t IN3;
    const uint8_t IN4;
};

struct Lidar1DPins {
    const uint8_t SDA;
    const uint8_t SCL;
};

namespace Pins {
    constexpr EnginePins FRONT_RIGHT  {32, 33, 25};
    constexpr EnginePins REAR_LEFT   {23, 22, 21};
    constexpr EnginePins FRONT_LEFT {17, 18, 16};
    constexpr EnginePins REAR_RIGHT  {26, 14, 27};
    constexpr StepperPins ROTATION_TOWER {5, 19, 15, 2};
    constexpr Lidar1DPins LIDAR_1D {4,13};
    constexpr int HALL_SENSOR {34};
}