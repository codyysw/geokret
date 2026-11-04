#include "NaiveAutonomous.hpp"

NaiveAutonomous::NaiveAutonomous(const ProximitySensor& proximity)
    : IDriveMode(),
      prox{proximity},
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
            if (prox.getDistance() < 30 and prox.getSignal() > 100) {
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
            return DriveCommand{DRIVE_POWER, -DRIVE_POWER};
        case State::STOPPED:
            return DriveCommand{0,0};
        default:
            return DriveCommand{0, 0}; // stop on unexpected
    }
}