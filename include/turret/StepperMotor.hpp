#pragma once

#include <AccelStepper.h>
#include "Config.hpp"

class StepperMotor
{
public: // CONFIGURABLE CONSTANTS
    static constexpr int STEPS_PER_ROTATION = 2048;
    static constexpr int MAX_STEPS_PER_SECOND = 512;
    static constexpr int ACCELERATION = 500;
    static constexpr long RUN_DISTANCE = 1000000000L;
public:
    StepperMotor(StepperPins pins, AccelStepper::MotorInterfaceType type = AccelStepper::FULL4WIRE);
    void begin();
    bool run();
    void rotateBy(int degrees);
    void rotateTo(int degrees);
    void rotateWithConstantSpeed(long stepsPerSecond);
    void setZeroHere();
    int getAngle() const;
    int getAngleToGo() const;
    void stop();
    bool isMoving() const;
private:
    static int getWrappedSteps(long steps);
    static int getWrappedDegrees(int degrees);
    static int stepsToDegrees(long steps);
    static float degreesToSteps(int degrees);
    float m_roundAdj = 0;
    bool m_constantSpeedMode = false;
    mutable AccelStepper motor;
};