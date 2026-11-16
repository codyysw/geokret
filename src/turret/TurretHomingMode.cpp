#include "TurretHomingMode.hpp"

void TurretHomingMode::enter()
{
    turret.rotateTo(0);
    homed = false;
}

void TurretHomingMode::updateTurretTarget()
{
    if (ctx.hall.isMagnetInRange()) {
        turret.stop();
        turret.setZeroHere();
        homed = true;
        return;
    }
    homed = false;
    if (!turret.isMoving()) {
        turret.rotateBy(5);
    }
}