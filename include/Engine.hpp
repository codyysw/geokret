#pragma once

#include <string>
#include <Arduino.h>
#include <algorithm>
#include "GamePadInput.hpp"
#include "Config.hpp"

class Engine
{
public: // CONFIGURABLE CONSTANTS
    static constexpr int MIN_POWER = 20;
    static constexpr int MAX_POWER = 255;
    static constexpr int ACCELERATION_RATE = 5;
    static constexpr int DECELERATION_RATE = 20;
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
    void stop();
    State getCurrentState() const;
    std::string getStateName(State state) const;

private:
    void modifyPower();
    void writeToMotorDriver() const;

    const EnginePins pins;
    int currentPower;
    int targetPower;
};