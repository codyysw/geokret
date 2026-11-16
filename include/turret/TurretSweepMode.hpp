#pragma once

#include "ITurretMode.hpp"

class TurretSweepMode : public ITurretMode
{
public: //CONFIGURABLE CONSTANTS
public:
    using ITurretMode::ITurretMode;
    void enter() override;
    void updateTurretTarget() override;
    int getCurrentAngle() { return turret.getAngle(); }
};