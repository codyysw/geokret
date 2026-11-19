#pragma once

#include "ITurretMode.hpp"

class TurretHomingMode : public ITurretMode
{
public: //CONFIGURABLE CONSTANTS
    static constexpr int HOMING_SPEED = 200;
    static constexpr int ALIGN_DEGREES = 14;
public:
    using ITurretMode::ITurretMode;
    void enter() override;
    void updateTurretTarget() override;
    bool isHomed() const { return currentState == State::DONE; }
private:
    enum class State {
        SETUP,
        SEARCHING,
        ALIGNING,
        DONE
    };
    State currentState = State::SETUP;
};