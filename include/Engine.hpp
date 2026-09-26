#pragma once

#include <Arduino.h>
#include "GamePadInput.hpp"

class Engine
{
public:
    enum class State
    {
        NEUTRAL,
        FORWARD,
        BACKWARD,
        BRAKE
    };
    Engine() : currentState{State::NEUTRAL}, currentPower{0} { }
    void drive(int power);
    static constexpr uint MIN_POWER = 70;
    static constexpr uint MAX_POWER = 255;

private:
    void modifyPower();
    void writeToMotorDriver() const;
    // Assumption: Engine power range is (70 ; 255)

    static constexpr uint ACCELERATION_RATE = 10;
    State currentState;
    uint currentPower;
    uint targetPower;
};