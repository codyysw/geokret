#pragma once

#include <Arduino.h>
#include <utility>
#include <tuple>
#include "Engine.hpp"
#include "GamePadInput.hpp"

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
    std::pair<float, float> getDriveModePowers(float rawX, float rawY);
    std::pair<float, float> getRotationModePowers(float rawX, float rawY);
    static float applyCurve(float v);
    static int toMotorPower(float power);

    GamePadInput pad;
    Engine frontLeft;
    Engine rearLeft;
    Engine frontRight;
    Engine rearRight;
};