#include "helpers.hpp"

namespace Helpers {

    void printPadInput(ControllerPtr ctl) 
    {
        Serial.printf(
            "idx=%d, dpad: 0x%02x, buttons: 0x%04x, axis L: %4d, %4d, axis R: %4d, %4d, brake: %4d, throttle: %4d, "
            "misc: 0x%02x, gyro x:%6d y:%6d z:%6d, accel x:%6d y:%6d z:%6d\n",
            ctl->index(),        // Controller Index
            ctl->dpad(),         // D-pad
            ctl->buttons(),      // bitmask of pressed buttons
            ctl->axisX(),        // (-511 - 512) left X Axis
            ctl->axisY(),        // (-511 - 512) left Y axis
            ctl->axisRX(),       // (-511 - 512) right X axis
            ctl->axisRY(),       // (-511 - 512) right Y axis
            ctl->brake(),        // (0 - 1023): brake button
            ctl->throttle(),     // (0 - 1023): throttle (AKA gas) button
            ctl->miscButtons(),  // bitmask of pressed "misc" buttons
            ctl->gyroX(),        // Gyro X
            ctl->gyroY(),        // Gyro Y
            ctl->gyroZ(),        // Gyro Z
            ctl->accelX(),       // Accelerometer X
            ctl->accelY(),       // Accelerometer Y
            ctl->accelZ()        // Accelerometer Z
        );
    }

} // namespace Helpers