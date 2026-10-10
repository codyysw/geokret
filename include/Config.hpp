#pragma once

#include <Arduino.h>

struct EnginePins {
    const int pwm;
    const int in1;
    const int in2;
};


namespace Pins {
    constexpr EnginePins FRONT_LEFT  {32, 25, 26};
    constexpr EnginePins REAR_LEFT   {0, 0, 0};
    constexpr EnginePins FRONT_RIGHT {18, 16, 17};
    constexpr EnginePins REAR_RIGHT  {0, 0, 0};
}