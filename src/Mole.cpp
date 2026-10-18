#include "Mole.hpp"
#include "Config.hpp"

/*
* OVERALL FLOW - HANDLED IN MULTIPLE COMPONENTS
    1. load ctl to GamePadInput
    2. Process input into engine instructions
    3. Update engine states
    4. Send instructions to real engine modules
*/

Mole::Mole() 
    : frontLeft{Pins::FRONT_LEFT}, 
      rearLeft{Pins::REAR_LEFT},
      frontRight{Pins::FRONT_RIGHT},
      rearRight{Pins::REAR_RIGHT}
{

}

void Mole::begin()
{
    frontLeft.begin();
    rearLeft.begin();

    frontRight.begin();
    rearRight.begin();
}

void Mole::tick(ControllerPtr ctl)
{
    pad.processData(ctl);
    driveEngines();
}

void Mole::emergencyStop()
{
    frontLeft.stop();
    frontRight.stop();
    rearLeft.stop();
    rearRight.stop();
}

void Mole::driveEngines()
{
    float rawY = pad.getLeftJoystick().getY();
    float rawX = pad.getLeftJoystick().getX();

    float leftPower = 0, rightPower = 0;

    if (pad.isXpressed()) {
        std::tie(leftPower, rightPower) = getRotationModePowers(rawX, rawY);
    }
    else {
        std::tie(leftPower, rightPower) = getDriveModePowers(rawX, rawY);
    }

    float normFactor = max(1.0f, max(fabsf(leftPower), fabsf(rightPower)));
    leftPower /= normFactor;
    rightPower /= normFactor;

    int leftPowerForMotor = Mole::toMotorPower(leftPower);
    int rightPowerForMotor = Mole::toMotorPower(rightPower);
    
    frontLeft.drive(leftPowerForMotor);
    rearLeft.drive(leftPowerForMotor);

    frontRight.drive(rightPowerForMotor);
    rearRight.drive(rightPowerForMotor);

    // For simulation purposes:
    Serial.println();
}

std::pair<float, float> Mole::getDriveModePowers(float rawX, float rawY)
{
    float x = applyCurve(rawX);
    float y = applyCurve(rawY);
    if (y < 0) {
        x = -x;
    }

    float leftPower = y + (x * Mole::TURN_FACTOR);
    float rightPower = y - (x * Mole::TURN_FACTOR);
    
    float maxPower = std::max(std::abs(leftPower), std::abs(rightPower));
    if (maxPower > 1.0f) {
        leftPower  /= maxPower;
        rightPower /= maxPower;
    }

    return {leftPower, rightPower};
}

std::pair<float, float> Mole::getRotationModePowers(float rawX, float rawY)
{
    float leftPower = Mole::POWER_FACTOR * rawX;
    float rightPower = Mole::POWER_FACTOR * (-rawX);

    return {leftPower, rightPower};
}

float Mole::applyCurve(float v)
{
    return v * std::abs(v);
}

int Mole::toMotorPower(float power) {
    power = constrain(power, -1.0f, 1.0f);
    if (fabsf(power) < 0.01f) {
        return 0;
    }

    int pwm = lroundf(Engine::MIN_POWER + fabsf(power) * (Engine::MAX_POWER - Engine::MIN_POWER));
    return power > 0 ? pwm : -pwm;
}

void Mole::printPadData() const
{
    pad.printData();
}