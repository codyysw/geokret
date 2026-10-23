#pragma once

#include "IDriveMode.hpp"

class NaiveAutonomous : public IDriveMode
{
public: // CONFIGURABLE CONSTANTS
    static constexpr int CLOCK_SWITCH = 100;
    static constexpr float DRIVE_POWER = 0.3;
    static constexpr float TURN_POWER = 0.1;
public:
    NaiveAutonomous();
    void enter() override;
    DriveCommand calculatePower(const DriveContext& ctx) override;
private:
    void handleStateSwitching();
    DriveCommand handleForwardMode();
    DriveCommand handleBackwardMode();
    DriveCommand handleStoppingMode();
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