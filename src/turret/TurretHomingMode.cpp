#include "TurretHomingMode.hpp"

void TurretHomingMode::enter()
{
    turret.stop();
    currentState = State::SETUP;
}

void TurretHomingMode::updateTurretTarget()
{
    switch(currentState)
    {
        // were done, setting zero and quitting
        case State::DONE:
        {
            return;
        }
        // get away from magnet. If done, start the rotation and go to SEARCHING phase
        case State::SETUP:
        {
            if (ctx.hall.isMagnetInRange()) { 
                if (!turret.isMoving()) {
                    turret.rotateWithConstantSpeed(-HOMING_SPEED);
                }
                return;
            }
            turret.stop();
            turret.rotateWithConstantSpeed(HOMING_SPEED);
            currentState = State::SEARCHING;
            break;
        }
        // rotate until magnet signal found. Then stop and delegate X degrees align rotation
        case State::SEARCHING:
        {
            if (ctx.hall.isMagnetInRange()) {
                turret.stop();
                turret.rotateBy(ALIGN_DEGREES);
                currentState = State::ALIGNING;
                return;
            }
            break;
        }
        // keep rotating. WHen done, set zero here and set status to DONE
        case State::ALIGNING:
        {
            if (turret.isMoving()) {
                return;
            }
            turret.setZeroHere();
            currentState = State::DONE;
            break;
        }
    }
}