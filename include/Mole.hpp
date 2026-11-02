#pragma once

#include <Arduino.h>
#include <utility>
#include <tuple>
#include "Engine.hpp"
#include "IDriveMode.hpp"
#include "ManualDriver.hpp"
#include "NaiveAutonomous.hpp"
#include "IntervalTimer.hpp"

class Mole
{
public:
    Mole();
    void begin();
    void tick(ControllerPtr ctl, const unsigned long& now);
    void emergencyStop();
    void printData() const;
    Mole(const Mole&) = delete;
private:
    void handleModeSwitching();
    bool isModeToChange() const;
    void driveEngines();
    static DriveCommand normalize(const DriveCommand& cmd);
    static int toMotorPower(float power);
    IntervalTimer enginesTimer;
    IntervalTimer sensorTimer;
    ManualDriver manual;
    NaiveAutonomous autonomous;
    IDriveMode* currentMode;
    DriveContext ctx;
    Engine frontLeft;
    Engine rearLeft;
    Engine frontRight;
    Engine rearRight;
};