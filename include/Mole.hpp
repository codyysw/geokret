#pragma once

#include "DriveTrain.hpp"
#include "StepperMotor.hpp"
#include "IDriveMode.hpp"
#include "ManualDriver.hpp"
#include "NaiveAutonomous.hpp"
#include "ITurretMode.hpp"
#include "TurretManualMode.hpp"
#include "TurretSweepMode.hpp"
#include "TurretHomingMode.hpp"
#include "IntervalTimer.hpp"
#include "HostComm.hpp"

class Mole
{
public:
    Mole(ILink& ilink);
    void begin();
    void tick(ControllerPtr ctl);
    void emergencyStop();
    void printData() const;
    Mole(const Mole&) = delete;

private:
    void handleModeSwitching();
    void switchDriveMode();
    void switchTurretMode();
    void driveEngines();
    void queueScanToHost();

    IntervalTimer enginesTimer;
    IntervalTimer sensorTimer;
    
    MoleContext ctx;
    StepperMotor turret;
    DriveTrain mainDriveTrain;

    ManualDriver manualDrive;
    NaiveAutonomous autonomousDrive;
    IDriveMode* currentDriveMode;

    TurretManualMode manualTurret;
    TurretSweepMode sweepTurret;
    TurretHomingMode homingTurret;
    ITurretMode* currentTurretMode;

    HostComm host;
};