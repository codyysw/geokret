#pragma once

#include <Arduino.h>
#include "Config.hpp"

class HallSensor
{
public:
    void begin() {
        pinMode(Pins::HALL_SENSOR, INPUT);
    }
    bool isMagnetInRange() const {
        return digitalRead(Pins::HALL_SENSOR) == LOW;
    }
};