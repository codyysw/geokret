#pragma once

#include <Arduino.h>
#include "Engine.hpp"
#include "GamePadInput.hpp"

class Mole
{
public:
    void tick(ControllerPtr ctl);
    void driveEngines();
    void printPadData() const;
private:
    GamePadInput pad;
    Engine frontLeft;
    Engine frontRight;

};