#pragma once

#include <Arduino.h>
#include <utility>
#include <tuple>
#include "Engine.hpp"
#include "GamePadInput.hpp"
#include "DriveMode.hpp"

class Mole
{
public: // CONFIGURABLE CONSTANTS
    static constexpr float TURN_FACTOR = 0.3;
    static constexpr float POWER_FACTOR = 0.3;
public:
    Mole();
    void begin();
    void tick(ControllerPtr ctl);
    void driveEngines();
    void emergencyStop();
    void printPadData() const;

private:
    DriveCommand getDriveModePowers(float rawX, float rawY);
    DriveCommand getRotationModePowers(float rawX, float rawY);
    static float applyCurve(float v);
    static int toMotorPower(float power);

    DriveContext ctx;
    Engine frontLeft;
    Engine rearLeft;
    Engine frontRight;
    Engine rearRight;
};