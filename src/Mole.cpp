#include "Mole.hpp"
#include "Config.hpp"
#include "Protocol.hpp"

Mole::Mole(ILink& ilink) 
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
      currentTurretMode{&homingTurret},
      host{ilink}
{

}

void Mole::begin()
{
    currentDriveMode->enter();
    currentTurretMode->enter();

    ctx.begin();

    turret.begin();

    mainDriveTrain.begin();

    host.begin();
}

void Mole::tick(ControllerPtr ctl)
{
    turret.run();

    if (sensorTimer.isReady()) {
        ctx.updateSensors();
        currentTurretMode->updateTurretTarget();
        queueScanToHost();
        host.update();
    }
    if (enginesTimer.isReady()) {
        if (ctl == nullptr or not ctl->isConnected()) {
            emergencyStop();
            return;
        }
        ctx.updatePad(ctl);
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
    switchDriveMode();
    switchTurretMode();
}

void Mole::switchDriveMode()
{
    if (not ctx.pad.buttonY().justPushed()) {
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

void Mole::switchTurretMode()
{
    if (ctx.pad.buttonA().justPushed()) {
        if (currentTurretMode == &manualTurret) {
            currentTurretMode = &sweepTurret;
        }
        else {
            currentTurretMode = &manualTurret;
        }
        currentTurretMode->enter();
        return;
    }
    if (ctx.pad.buttonB().justPushed()) {
        if (currentTurretMode != &homingTurret) {
            currentTurretMode = &homingTurret;
        }
        currentTurretMode->enter();
    }
    
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

void Mole::queueScanToHost()
{
    Packets::ScanPoint scan
    {
        turret.getAngle(),
        ctx.prox.getDistance(),
        ctx.prox.getSignal(),
        millis()
    };
    host.queueScan(scan);
}