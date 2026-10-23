#include "NaiveAutonomous.hpp"

NaiveAutonomous::NaiveAutonomous()
    : IDriveMode(), 
      timer{0}, 
      currentState{State::STOPPED},
      prevState{State::STOPPED}
{

}

void NaiveAutonomous::begin()
{
    timer = 0;
    currentState = State::STOPPED;
    prevState = State::STOPPED;
}

DriveCommand NaiveAutonomous::calculatePower(const DriveContext& ctx)
{
    if (timer >= CLOCK_SWITCH) {
        State currentCopy = currentState;
        switch(currentState) 
        {
            case (State::FORWARD):
                currentState = State::STOPPED;
                break;
            case (State::BACKWARD):
                currentState = State::STOPPED;
                break;
            default:
                if (prevState == State::FORWARD) {
                    currentState = State::BACKWARD;
                }
                else if (prevState == State::BACKWARD) {
                    currentState = State::FORWARD;
                }
                else {
                    currentState = State::STOPPED;
                }
        }
        prevState = currentCopy;
    }

    timer += 1;
    switch (currentState)
    {
        case State::FORWARD:
            return handleForwardMode();
        case State::BACKWARD:
            return handleBackwardMode();
        default:
            return handleStoppingMode();
    }
}


DriveCommand NaiveAutonomous::handleForwardMode()
{
    return DriveCommand{DRIVE_POWER, DRIVE_POWER};
}

DriveCommand NaiveAutonomous::handleBackwardMode()
{
    return DriveCommand{-DRIVE_POWER, -DRIVE_POWER};
}

DriveCommand NaiveAutonomous::handleStoppingMode()
{
    return DriveCommand{0, 0};
}