#pragma once

#include "IDriveMode.hpp"
#include "ProximitySensor.hpp"

class NaiveAutonomous : public IDriveMode
{
public: // CONFIGURABLE CONSTANTS
    static constexpr int CLOCK_SWITCH = 100;
    static constexpr float DRIVE_POWER = 0.15;
    static constexpr float TURN_POWER = 0.1;
public:
    NaiveAutonomous(const ProximitySensor& proximity);
    void enter() override;
    DriveCommand calculatePower() override;
private:
    void handleStateSwitching();
    DriveCommand handleForwardMode();
    DriveCommand handleBackwardMode();
    DriveCommand handleStoppingMode();
    const ProximitySensor& prox;
    enum class State
    {
        FORWARD,
        BACKWARD,
        STOPPED
    };
    int timer;
    State currentState;
    State prevState;
};