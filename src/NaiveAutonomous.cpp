#include "NaiveAutonomous.hpp"

NaiveAutonomous::NaiveAutonomous(const DriveContext& ctx_)
    : IDriveMode{ctx_},
      turnTimer{0}, 
      currentState{State::FORWARD},
      prevState{State::BACKWARD}
{

}

void NaiveAutonomous::enter()
{
    turnTimer = 0;
    currentState = State::FORWARD;
    prevState = State::BACKWARD;
}

DriveCommand NaiveAutonomous::calculatePower()
{
    handleStateSwitching();
    return getCommandForCurrentState();
}

void NaiveAutonomous::handleStateSwitching()
{
    switch (currentState) 
    {
        case State::FORWARD:
        // TODO implement signal logic in ProximitySensor itself.
            if (ctx.prox.getDistance() < 30 and ctx.prox.getSignal() > 100) {
                currentState = State::TURNING;
            }
            return;
        case State::TURNING:
            turnTimer++;
            if (turnTimer < CLOCK_SWITCH) {
                return;
            }
            currentState = State::FORWARD;
            turnTimer = 0;
        default:
            currentState = State::FORWARD;
            return;
    }
}

DriveCommand NaiveAutonomous::getCommandForCurrentState() const
{
    switch (currentState)
    {
        case State::FORWARD:
            return DriveCommand{DRIVE_POWER, DRIVE_POWER};
        case State::BACKWARD:
            return DriveCommand{-DRIVE_POWER, -DRIVE_POWER};
        case State::TURNING:
            return DriveCommand{TURN_POWER, -TURN_POWER};
        case State::STOPPED:
            return DriveCommand{0,0};
        default:
            return DriveCommand{0, 0}; // stop on unexpected
    }
}