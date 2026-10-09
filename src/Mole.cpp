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

void Mole::begin() const
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
    // * classic arcade. Flaw: turn radius is reversed proportional to speed. 
    // * It might be unintuitive. 
    // * Also, no guarantee of no-backward power on sharp turns.
    float leftPower = rawY + (rawX * Mole::TURN_FACTOR);
    float rightPower = rawY - (rawX * Mole::TURN_FACTOR);
    
    // * car-like. Huge flaw: on X = MAX, Y = 0, it does not turn !
    // float leftPower = rawY + (fabsf(rawY) * rawX * Mole::TURN_FACTOR);
    // float rightPower = rawY - (fabsf(rawY) * rawX * Mole::TURN_FACTOR);

    // * CLANKER HYBRID, I have no understanding of that
    // const float TURN_BASE = 0.4f;
    // float turn = rawX * Mole::POWER_FACTOR * 
    // (TURN_BASE + (1.0f - TURN_BASE) * fabsf(rawY));

    // float leftPower  = y + turn;
    // float rightPower = y - turn;

    return {leftPower, rightPower};
}

std::pair<float, float> Mole::getRotationModePowers(float rawX, float rawY)
{
    float leftPower = Mole::POWER_FACTOR * rawY + rawX;
    float rightPower = Mole::POWER_FACTOR * rawY - rawX;

    return {leftPower, rightPower};
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