#include "TurretManualMode.hpp"

void TurretManualMode::updateTurretTarget()
{
    float x = ctx.pad.getRightJoystick().getX();
    if (x < 0) {
        alreadyStopped = false;
        turret.rotateTo(-RUN_DISTANCE);
        return;
    }
    if (x > 0) {
        alreadyStopped = false;
        turret.rotateTo(RUN_DISTANCE);
        return;
    }
    if (!alreadyStopped) {
        alreadyStopped = true;
        turret.stop();
    }
}