#include "ManualDriver.hpp"



DriveCommand ManualDriver::calculatePower(const DriveContext& ctx)
{
    float rawY = ctx.pad.getLeftJoystick().getY();
    float rawX = ctx.pad.getLeftJoystick().getX();

    if (ctx.pad.buttonX().isDown()) {
        return getRotationModePowers(rawX);
    }
    return getDriveModePowers(rawX, rawY);
}

DriveCommand ManualDriver::getRotationModePowers(float rawX) const
{
    float leftPower = ManualDriver::POWER_FACTOR * rawX;
    float rightPower = ManualDriver::POWER_FACTOR * (-rawX);

    return DriveCommand{leftPower, rightPower};
}

DriveCommand ManualDriver::getDriveModePowers(float rawX, float rawY) const
{
    float x = applyCurve(rawX);
    float y = applyCurve(rawY);
    if (y < 0) {
        x = -x;
    }

    float leftPower = y + (x * ManualDriver::TURN_FACTOR);
    float rightPower = y - (x * ManualDriver::TURN_FACTOR);
    
    float maxPower = std::max(std::abs(leftPower), std::abs(rightPower));
    if (maxPower > 1.0f) {
        leftPower  /= maxPower;
        rightPower /= maxPower;
    }

    return DriveCommand{leftPower, rightPower};
}

float ManualDriver::applyCurve(float v)
{
    return v * std::abs(v);
}