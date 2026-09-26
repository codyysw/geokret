#include "Mole.h"


/*
* OVERALL FLOW - HANDLED IN MULTIPLE COMPONENTS
    1. load ctl to GamePadInput
    2. Process input into engine instructions
    3. Update engine states
    4. Send instructions to real engine modules
*/

void Mole::tick(ControllerPtr ctl)
{
    pad.processData(ctl);
    driveEngines();
}

void Mole::driveEngines()
{
    /*
        TODO convert pad input into engines power:
        * Send only power in range (MIN_POWER, MAX_POWER)
        * Engine handles its states itself 
        * The code below is a simplification for test purposes
    */
    int rawY = pad.getLeftJoystick().getY();
    int mappedPower = 0;

    if (rawY > 0) {
        mappedPower = map(rawY, 200, 512, Engine::MIN_POWER, Engine::MAX_POWER);
    }
    else if (rawY < 0) {
        mappedPower = map(rawY, -511, -200, -Engine::MAX_POWER, -Engine::MIN_POWER);
    }
    else {
        mappedPower = 0;
    }
    
    frontLeft.drive(mappedPower);
    frontRight.drive(mappedPower);

    // For simulation purposes:
    Serial.println();
}

void Mole::printPadData() const
{
    pad.printData();
}