#pragma once
#include "GamePadInput.hpp"

struct DriveCommand {
    constexpr DriveCommand(float l = 0.f, float r = 0.f) : left(l), right(r) {}
    float left;
    float right;
};

struct DriveContext {
    GamePadInput pad;
    void update(ControllerPtr ctl) {
        pad.processData(ctl);
    }
};

