#pragma once

#include "GamePadInput.hpp"

struct DriveCommand 
{
    constexpr DriveCommand(float l = 0, float r = 0) : left(l), right(r) {}
    float left;
    float right;
};

struct DriveContext 
{
    GamePadInput pad;
    void update(ControllerPtr ctl) {
        pad.processData(ctl);
    }
    void printData() const {
        pad.printData();
    }
};

class IDriveMode
{
public:
    IDriveMode() = default;
    virtual ~IDriveMode() = default;
    virtual DriveCommand calculatePower(const DriveContext& ctx) = 0;
};