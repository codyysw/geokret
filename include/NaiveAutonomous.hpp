#pragma once

#include "IDriveMode.hpp"

class NaiveAutonomous : public IDriveMode
{
public: // CONFIGURABLE CONSTANTS
    static constexpr int CLOCK_SWITCH = 20;
    static constexpr int DRIVE_POWER = 70;
    static constexpr int TURN_POWER = 30;
public:
    NaiveAutonomous();
    void begin() override;
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