#pragma once

#include <Arduino.h>
#include <utility>
#include <tuple>
#include "Engine.hpp"
#include "StepperMotor.hpp"
#include "IDriveMode.hpp"
#include "ManualDriver.hpp"
#include "NaiveAutonomous.hpp"
#include "ITurretMode.hpp"
#include "TurretManualMode.hpp"
#include "TurretSweepMode.hpp"
#include "TurretHomingMode.hpp"
#include "IntervalTimer.hpp"

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
    void handleModeSwitching();
    bool isModeToChange() const;
    void driveEngines();
    static DriveCommand normalize(const DriveCommand& cmd);
    static int toMotorPower(float power);

    IntervalTimer enginesTimer;
    IntervalTimer sensorTimer;
    ManualDriver manualDrive;
    NaiveAutonomous autonomousDrive;
    IDriveMode* currentDriveMode;
    TurretManualMode manualTurret;
    TurretSweepMode sweepTurret;
    TurretHomingMode homingTurret;
    ITurretMode* currentTurretMode;
    MoleContext ctx;

    
    StepperMotor turret;
    Engine frontLeft;
    Engine rearLeft;
    Engine frontRight;
    Engine rearRight;
};