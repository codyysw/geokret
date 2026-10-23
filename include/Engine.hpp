#pragma once

#include <string>
#include <Arduino.h>
#include <algorithm>
#include "GamePadInput.hpp"
#include "Config.hpp"

class Engine
{
public: // CONFIGURABLE CONSTANTS
    static constexpr int MIN_POWER = 15;
    static constexpr int MAX_POWER = 255;
    static constexpr int ACCELERATION_RATE = 10;
    static constexpr int DECELERATION_RATE = 40;
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
    static const char* getStateName(State state);

private:
    void modifyPower();
    void writeToMotorDriver() const;

    const EnginePins pins;
    int currentPower;
    int targetPower;
};