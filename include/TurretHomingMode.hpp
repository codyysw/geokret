#pragma once

#include "ITurretMode.hpp"

class TurretHomingMode : public ITurretMode
{
public: //CONFIGURABLE CONSTANTS
public:
    using ITurretMode::ITurretMode;
    void enter() override;
    void updateTurretTarget() override;
    bool isHomed() const { return homed; }
private:
    bool homed = false;
};