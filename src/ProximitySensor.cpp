#include <Arduino.h>

#include "ProximitySensor.hpp"
#include "Config.hpp"

void ProximitySensor::begin()
{
    Serial2.begin(115200, SERIAL_8N1, Pins::Lidar1D.RXD, Pins::Lidar1D.TXD);
    Serial.println("connection with LIDAR initialized");
}

void ProximitySensor::updateData()
{
    if (not (Serial2.available() >= 9)) {
        Serial.println("invalid LIDAR buffer size");
        return;
    }
    if (not (Serial2.read() == 0x59) or not(Serial2.read() == 0x59)) {
        Serial.println("invalid LIDAR frame header");
        return;
    }
    uint8_t buf[7];
    Serial2.readBytes(buf, 7);

    if (not isCheckSumCorrect(buf)) { 
        Serial.println("LIDAR checksum is invalid");  
        return;
    }
    distance = buf[0] | (buf[1] << 8);
    signal = buf[2] | (buf[3] << 8);
    temperature = 0;
}

bool ProximitySensor::isCheckSumCorrect(const uint8_t* buf)
{
    uint8_t checksum = 0x59 + 0x59;
    for (int i = 0; i < 6; i++) {
        checksum += buf[i];
    }
    return checksum == buf[6];
}