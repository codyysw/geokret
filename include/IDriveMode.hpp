#pragma once

#include "GamePadInput.hpp"
#include "ProximitySensor.hpp"
#include "HallSensor.hpp"

struct DriveCommand 
{
    constexpr DriveCommand(float l = 0, float r = 0) : left(l), right(r) {}
    float left;
    float right;
};

struct DriveContext 
{
    GamePadInput pad;
    ProximitySensor prox;
    HallSensor hall;
    void begin() {
        prox.begin();
        hall.begin();
    }
    void updatePad(ControllerPtr ctl) {
        pad.processData(ctl);
    }
    void updateSensors() {
        prox.updateData();
    }
    void printData() const {
        pad.printData();
    }
};

class IDriveMode
{
protected:
    const DriveContext& ctx;
public:
    IDriveMode(const DriveContext& ctx_) : ctx{ctx_} { }
    virtual ~IDriveMode() = default;
    virtual void enter() { }
    virtual DriveCommand calculatePower() = 0;
};