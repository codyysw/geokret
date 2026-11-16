#include "Mole.hpp"
#include "Config.hpp"

Mole::Mole() 
    : enginesTimer{IntervalsMs::ENGINE},
      sensorTimer{IntervalsMs::SENSOR},
      turret{Pins::ROTATION_TOWER},
      mainDriveTrain{},
      manualDrive{ctx},
      autonomousDrive{ctx},
      currentDriveMode{&manualDrive},
      manualTurret{ctx, turret},
      sweepTurret{ctx, turret},
      homingTurret{ctx, turret},
      currentTurretMode{&homingTurret}
{
    
}

void Mole::begin()
{
    currentDriveMode->enter();
    currentTurretMode->enter();

    ctx.begin();

    turret.begin();

    mainDriveTrain.begin();
}

void Mole::tick(ControllerPtr ctl)
{
    turret.run();

    if (sensorTimer.isReady()) {
        ctx.updateSensors();
        currentTurretMode->updateTurretTarget();
    }
    if (enginesTimer.isReady()) {
        if (ctl == nullptr or not ctl->isConnected()) {
            emergencyStop();
            return;
        }
        ctx.updatePad(ctl);
        // if (ctx.pad.buttonA().justPushed()) {
        //     turret.tmpMoveAround(ctx);
        // }
        handleModeSwitching();
        driveEngines();
    }
}

void Mole::emergencyStop()
{
    mainDriveTrain.stopAllEngines();

    if (currentDriveMode != &manualDrive) {
        currentDriveMode = &manualDrive;
        currentDriveMode->enter();
    }
    if (currentTurretMode != &manualTurret and currentTurretMode != &homingTurret) {
        currentTurretMode = &manualTurret;
        currentTurretMode->enter();
    }
}

void Mole::handleModeSwitching()
{
    if (not isModeToChange()) {
        return;
    }
    if (currentDriveMode == &manualDrive) {
        currentDriveMode = &autonomousDrive;
    }
    else {
        currentDriveMode = &manualDrive;
    }
    currentDriveMode->enter();
}

bool Mole::isModeToChange() const
{
    // switching mode on pushing Y button
    return ctx.pad.buttonY().justPushed();
}

void Mole::driveEngines()
{
    DriveCommand command = currentDriveMode->calculatePower();

    mainDriveTrain.drive(command);
}

void Mole::printData() const
{
    ctx.printData();
}