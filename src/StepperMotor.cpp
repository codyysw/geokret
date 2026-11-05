#include "StepperMotor.hpp"

StepperMotor::StepperMotor(StepperPins pins, 
    AccelStepper::MotorInterfaceType type)
    : motor{type, pins.IN1, pins.IN3, pins.IN2,pins.IN4}
{

}

void StepperMotor::begin()
{
    motor.setAcceleration(ACCELERATION);
    motor.setMaxSpeed(MAX_STEPS_PER_SECOND);
    // TODO it should be recentered using hall sensor at the beginning
}

void StepperMotor::tmpMoveWithPad(const DriveContext& ctx)
{
    float x = ctx.pad.getRightJoystick().getX();
    int32_t maxDist = uint32_t(-1) >> 1;
    if (x < 0) {
        move(-maxDist);
        return;
    }
    if (x > 0) {
        move(maxDist);
        return;
    }
    stop();
}