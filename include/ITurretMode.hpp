#pragma once

#include "IDriveMode.hpp"
#include "StepperMotor.hpp"

class ITurretMode
{
protected:
    const MoleContext& ctx;
    StepperMotor& turret;
public:
    ITurretMode(const MoleContext& ctx_, StepperMotor& t) 
        : ctx{ctx_}, turret{t} { }
    virtual ~ITurretMode() = default;
    virtual void enter() { }
    virtual void updateTurretTarget() = 0;
};