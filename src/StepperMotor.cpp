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
    if (x < 0) {
        stopped = false;
        moveTo(-RUN_DISTANCE);
        return;
    }
    if (x > 0) {
        stopped = false;
        moveTo(RUN_DISTANCE);
        return;
    }
    if (not stopped) {
        stopped = true;
        stop();
    }
}