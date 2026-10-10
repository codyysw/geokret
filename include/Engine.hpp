#pragma once

#include <string>
#include <Arduino.h>
#include "GamePadInput.hpp"
#include "Config.hpp"

class Engine
{
public:
    explicit Engine(const EnginePins& pins);
    enum class State
    {
        NEUTRAL,
        FORWARD,
        BACKWARD,
        BRAKE
    };
    void begin();
    void drive(int power);
    State getCurrentState() const;
    std::string getStateName(State state) const;
    static constexpr int MIN_POWER = 70;
    static constexpr int MAX_POWER = 255;

private:
    void modifyPower();
    void writeToMotorDriver() const;
    // Assumption: Engine power range is (70 ; 255)

    static constexpr int ACCELERATION_RATE = 5;
    const EnginePins pins;
    int currentPower;
    int targetPower;
};