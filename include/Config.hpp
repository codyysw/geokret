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
    constexpr EnginePins FRONT_RIGHT  {32, 25, 26};
    constexpr EnginePins REAR_LEFT   {23, 22, 21};
    constexpr EnginePins FRONT_LEFT {18, 17, 16};
    constexpr EnginePins REAR_RIGHT  {33, 27, 19};
}