#pragma once

#include <cmath>

struct DriveCommand
{
    constexpr DriveCommand(float l = 0, float r = 0) : left(l), right(r) { }
    DriveCommand getNormalized() const{
        const float norm = std::max(
            1.0f,
            std::max(
                fabsf(left),
                fabsf(right)
            )
        );
        return DriveCommand{left / norm, right / norm};
    }
    float left;
    float right;
};