#pragma once

#include <Wire.h>
#include <TFLI2C.h>

class ProximitySensor
{
public:
    static constexpr int16_t MAX_DISTANCE = 800;
    static constexpr uint16_t MIN_SIGNAL   = 100;
    void begin();
    bool updateData();
    int16_t getDistance() const { return distance; }
    uint16_t getSignal() const { return signal; }
    float getTemperature() const { return temperature; }
private:
    TFLI2C lidar;
    static constexpr uint8_t I2C_ADDR = TFL_DEF_ADR;
    int16_t distance = 0;
    int16_t signal = 0;
    float temperature = 0;
};