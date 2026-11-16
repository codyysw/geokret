#pragma once

#include "DriveCommand.hpp"
#include "Engine.hpp"

class DriveTrain
{
public: // CONFIGURABLE CONSTANTS

public:
    DriveTrain();
    void begin();
    void stopAllEngines();
    void drive(const DriveCommand& cmd);
private:
    static int toMotorPower(float power);

    Engine frontLeft;
    Engine rearLeft;
    Engine frontRight;
    Engine rearRight; 
};