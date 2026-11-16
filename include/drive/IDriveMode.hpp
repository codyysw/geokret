#pragma once

#include "MoleContext.hpp"
#include "DriveCommand.hpp"

class IDriveMode
{
protected:
    const MoleContext& ctx;
public:
    IDriveMode(const MoleContext& ctx_) : ctx{ctx_} { }
    virtual ~IDriveMode() = default;
    virtual void enter() { }
    virtual DriveCommand calculatePower() = 0;
};