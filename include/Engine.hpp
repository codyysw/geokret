#pragma once

#include <string>
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
    Engine() : targetState{State::NEUTRAL}, currentPower{0} { }
    void drive(int power);
    std::string getCurrentStateName() const;
    static constexpr int MIN_POWER = 70;
    static constexpr int MAX_POWER = 255;

private:
    void modifyPower();
    void writeToMotorDriver() const;
    // Assumption: Engine power range is (70 ; 255)

    static constexpr int ACCELERATION_RATE = 10;
    State targetState;
    int currentPower;
    int targetPower;
};