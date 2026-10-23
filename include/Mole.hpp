#pragma once

#include <Arduino.h>
#include <utility>
#include <tuple>
#include "Engine.hpp"
#include "IDriveMode.hpp"
#include "ManualDriver.hpp"

class Mole
{
public:
    Mole();
    void begin();
    void tick(ControllerPtr ctl);
    void emergencyStop();
    void printData() const;
    Mole(const Mole&) = delete;
private:
    void driveEngines();
    static int toMotorPower(float power);
    ManualDriver manual;
    IDriveMode* currentMode;
    DriveContext ctx;
    Engine frontLeft;
    Engine rearLeft;
    Engine frontRight;
    Engine rearRight;
};