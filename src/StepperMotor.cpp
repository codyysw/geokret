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
    m_roundAdj = 0;
    // TODO it should be recentered using hall sensor at the beginning
}

int StepperMotor::getWrappedSteps(long steps)
{
    int wrapped = steps % STEPS_PER_ROTATION;
    return (wrapped < 0) ? (wrapped + STEPS_PER_ROTATION) : wrapped; // Y = [0,2048)
}

int StepperMotor::getWrappedDegrees(int degrees)
{
    int wrapped = degrees % 360;
    return (wrapped < 0) ? (wrapped + 360) : wrapped; // Y = [0,360)
}

int StepperMotor::stepsToDegrees(long steps)
{
    int wrapped = getWrappedSteps(steps);
    int out = static_cast<int>(roundf(wrapped * (360.0f / STEPS_PER_ROTATION)));
    return (out != 360) ? out : 0;    
}

float StepperMotor::degreesToSteps(int degrees)
{
    return degrees * (STEPS_PER_ROTATION / 360.0f);
}

int StepperMotor::getAngle() const
{
    return stepsToDegrees(motor.currentPosition());
}

int StepperMotor::getAngleToGo() const
{
    return stepsToDegrees(motor.distanceToGo());
}

void StepperMotor::rotateBy(int degrees)
{
    float stepsToGo = degreesToSteps(degrees);
    int stepsToGoRounded = static_cast<int>(roundf(stepsToGo));
    m_roundAdj += (stepsToGo - stepsToGoRounded);
    int adjToAdd = static_cast<int>(m_roundAdj);
    m_roundAdj -= adjToAdd;
    long delta = stepsToGoRounded + adjToAdd;
    motor.moveTo(motor.targetPosition() + delta);
}

void StepperMotor::rotateTo(int degrees)
{
    int degreesWrapped = getWrappedDegrees(degrees);
    int currentAngle = getAngle();
    rotateBy(degreesWrapped - currentAngle);
}

void StepperMotor::tmpMoveAround(const DriveContext& ctx)
{
    if (isMoving()) {
        return;
    }
    this->rotateBy(direction*360);
    direction = -direction;
    return;

    float x = ctx.pad.getRightJoystick().getX();
    if (x < 0) {
        direction = false;
        motor.moveTo(-RUN_DISTANCE);
        return;
    }
    if (x > 0) {
        direction = false;
        motor.moveTo(RUN_DISTANCE);
        return;
    }
    if (not direction) {
        direction = true;
        stop();
    }
}