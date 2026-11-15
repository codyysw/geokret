#pragma once


namespace IntervalsMs {
    constexpr int ENGINE = 25;
    constexpr int SENSOR = 10;
}

struct EnginePins {
    const int pwm;
    const int in1;
    const int in2;
};

struct StepperPins {
    const int IN1;
    const int IN2;
    const int IN3;
    const int IN4;
};

struct Lidar1DPins {
    const int SDA; // Receiving/Data
    const int SCL; // Transmitting/Clock
};

namespace Pins {
    constexpr EnginePins FRONT_RIGHT  {32, 33, 25};
    constexpr EnginePins REAR_LEFT   {23, 22, 21};
    constexpr EnginePins FRONT_LEFT {17, 18, 16};
    constexpr EnginePins REAR_RIGHT  {26, 14, 27};
    constexpr StepperPins ROTATION_TOWER {5, 19, 15, 2};
    constexpr Lidar1DPins LIDAR_1D {4,13};
    constexpr int HALL_SENSOR {-1};
}