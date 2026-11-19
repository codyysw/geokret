#include <Arduino.h>
#include <cmath>

#include "DriveTrain.hpp"
#include "Config.hpp"

DriveTrain::DriveTrain()
    : frontLeft{Pins::FRONT_LEFT}, 
      rearLeft{Pins::REAR_LEFT},
      frontRight{Pins::FRONT_RIGHT},
      rearRight{Pins::REAR_RIGHT}
{

}

void DriveTrain::begin()
{
    frontLeft.begin();
    rearLeft.begin();

    frontRight.begin();
    rearRight.begin();
}

void DriveTrain::stopAllEngines()
{
    frontLeft.stop();
    frontRight.stop();
    rearLeft.stop();
    rearRight.stop();
}

void DriveTrain::drive(const DriveCommand& cmd)
{
    DriveCommand normCmd = cmd.getNormalized();
    int leftPowerForMotor = toMotorPower(normCmd.left);
    int rightPowerForMotor = toMotorPower(normCmd.right);
    
    frontLeft.drive(leftPowerForMotor);
    rearLeft.drive(leftPowerForMotor);

    frontRight.drive(rightPowerForMotor);
    rearRight.drive(rightPowerForMotor);
}

int DriveTrain::toMotorPower(float power)
{
    if (!std::isfinite(power)) {
        return 0;
    }
    power = constrain(power, -1.0f, 1.0f);
    if (fabsf(power) < 0.01f) {
        return 0;
    }

    int pwm = lroundf(Engine::MIN_POWER + fabsf(power) * (Engine::MAX_POWER - Engine::MIN_POWER));
    return power > 0 ? pwm : -pwm;
}