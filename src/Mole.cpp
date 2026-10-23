#include "Mole.hpp"
#include "Config.hpp"

Mole::Mole() 
    : manual{},
      autonomous{},
      currentMode{&autonomous},
      frontLeft{Pins::FRONT_LEFT}, 
      rearLeft{Pins::REAR_LEFT},
      frontRight{Pins::FRONT_RIGHT},
      rearRight{Pins::REAR_RIGHT}

{
    currentMode->begin();
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
    ctx.update(ctl);
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
    DriveCommand command = currentMode->calculatePower(this->ctx);

    int leftPowerForMotor = Mole::toMotorPower(command.left);
    int rightPowerForMotor = Mole::toMotorPower(command.right);
    
    frontLeft.drive(leftPowerForMotor);
    rearLeft.drive(leftPowerForMotor);

    frontRight.drive(rightPowerForMotor);
    rearRight.drive(rightPowerForMotor);
}

int Mole::toMotorPower(float power) {
    power = constrain(power, -1.0f, 1.0f);
    if (fabsf(power) < 0.01f) {
        return 0;
    }

    int pwm = lroundf(Engine::MIN_POWER + fabsf(power) * (Engine::MAX_POWER - Engine::MIN_POWER));
    return power > 0 ? pwm : -pwm;
}

void Mole::printData() const
{
    ctx.printData();
}