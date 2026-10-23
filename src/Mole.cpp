#include "Mole.hpp"
#include "Config.hpp"

Mole::Mole() 
    : manual{},
      autonomous{},
      currentMode{&manual},
      frontLeft{Pins::FRONT_LEFT}, 
      rearLeft{Pins::REAR_LEFT},
      frontRight{Pins::FRONT_RIGHT},
      rearRight{Pins::REAR_RIGHT}

{
    
}

void Mole::begin()
{
    currentMode->enter();
    
    frontLeft.begin();
    rearLeft.begin();

    frontRight.begin();
    rearRight.begin();
}

void Mole::tick(ControllerPtr ctl)
{
    ctx.update(ctl);
    handleModeSwitching();
    driveEngines();
}

void Mole::emergencyStop()
{
    frontLeft.stop();
    frontRight.stop();
    rearLeft.stop();
    rearRight.stop();

    currentMode = &manual;
    currentMode->enter();
}

void Mole::handleModeSwitching()
{
    if (not isModeToChange()) {
        return;
    }

    if (currentMode == &manual) {
        Serial.println("SWITCH TO AUTO");
        currentMode = &autonomous;
    }
    else {
        Serial.println("SWITCH TO MANUAL");
        currentMode = &manual;
    }
    currentMode->enter();
}

bool Mole::isModeToChange() const
{
    // switching mode on pushing Y button
    return ctx.pad.buttonY().justPushed();
}

void Mole::driveEngines()
{
    DriveCommand command = normalize(currentMode->calculatePower(this->ctx));

    int leftPowerForMotor = Mole::toMotorPower(command.left);
    int rightPowerForMotor = Mole::toMotorPower(command.right);
    
    frontLeft.drive(leftPowerForMotor);
    rearLeft.drive(leftPowerForMotor);

    frontRight.drive(rightPowerForMotor);
    rearRight.drive(rightPowerForMotor);
}

DriveCommand Mole::normalize(const DriveCommand& cmd)
{
    const float norm = std::max(
        1.0f,
        std::max(
            fabsf(cmd.left),
            fabsf(cmd.right)
        )
    );
    return DriveCommand{cmd.left / norm, cmd.right / norm};
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