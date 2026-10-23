#pragma once
#include "IDriveMode.hpp"

class ManualDriver : public IDriveMode
{
public: // CONFIGURABLE CONSTANTS
    static constexpr float TURN_FACTOR = 0.3;
    static constexpr float POWER_FACTOR = 0.3;
public:
    ManualDriver() = default;
    DriveCommand calculatePower(const DriveContext& ctx) override;
private:
    DriveCommand getDriveModePowers(float rawX, float rawY) const;
    DriveCommand getRotationModePowers(float rawX) const;
    static float applyCurve(float v);
};