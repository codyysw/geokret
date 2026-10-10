#pragma once

#include <Arduino.h>

const int STDBY1 = 13;
const int STDBY2 = 14;

struct EnginePins {
    const int pwm;
    const int in1;
    const int in2;
};


namespace Pins {
    constexpr EnginePins FRONT_LEFT  {32, 25, 26};
    constexpr EnginePins REAR_LEFT   {23, 21, 22};
    constexpr EnginePins FRONT_RIGHT {18, 16, 17};
    constexpr EnginePins REAR_RIGHT  {33, 19, 27};
}