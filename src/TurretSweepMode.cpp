#include "TurretSweepMode.hpp"

void TurretSweepMode::enter()
{
    turret.rotateTo(0);
}

void TurretSweepMode::updateTurretTarget()
{
    if (!turret.isMoving()) {
        turret.rotateBy(360);
    }
}