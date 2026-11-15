#include <Arduino.h>

#include "ProximitySensor.hpp"
#include "Config.hpp"

void ProximitySensor::begin()
{
    Wire.begin(Pins::LIDAR_1D.SDA, Pins::LIDAR_1D.SCL);
    Wire.setClock(400000);
    Wire.setTimeOut(5);
    Serial.println("connection with LIDAR initialized");
}

bool ProximitySensor::updateData()
{
    int16_t rawDistCm, rawSignal, rawTempHundreths;
    bool success = lidar.getData(rawDistCm, rawSignal, rawTempHundreths, I2C_ADDR);
    distance = rawDistCm;
    signal = rawSignal;
    temperature = static_cast<float>(rawTempHundreths) / 100.0;
    return true;

}