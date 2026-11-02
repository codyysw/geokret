#pragma once

class ProximitySensor
{
public:
    void begin();
    void updateData();
    int16_t getDistance() const { return distance; }
    uint16_t getSignal() const { return signal; }
    float getTemperature() const { return temperature; }
private:
    static bool isCheckSumCorrect(const uint8_t* buf);
    int16_t distance = 0;
    uint16_t signal = 0;
    float temperature = 0;
};