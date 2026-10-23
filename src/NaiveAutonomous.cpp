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
    handleStateSwitching();

    timer++;
    switch (currentState)
    {
        case (State::FORWARD):
            Serial.printf("F");
            return handleForwardMode();
        case (State::BACKWARD):
            Serial.printf("B");
            return handleBackwardMode();
        default:
            Serial.printf("S");
            return handleStoppingMode();
    }
}

void NaiveAutonomous::handleStateSwitching()
{
    if (timer < CLOCK_SWITCH) {
        return;
    }
    
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
            if (prevState == State::BACKWARD) 
            {
                currentState = State::FORWARD;
            }
            else 
            {
                currentState = State::BACKWARD;
            }
    }
    prevState = currentCopy;
    timer = 0;
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