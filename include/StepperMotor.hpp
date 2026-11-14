#pragma once

#include <AccelStepper.h>
#include "Config.hpp"
#include "IDriveMode.hpp"

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
    bool run() { return motor.run(); }
    void rotateBy(int degrees);
    void rotateTo(int degrees);
    int getAngle() const;
    int getAngleToGo() const;
    void stop() { motor.stop(); }
    bool isMoving() const { return motor.distanceToGo() != 0; }

    void tmpMoveAround(const DriveContext& ctx);
private:
    static int getWrappedSteps(long steps);
    static int getWrappedDegrees(int degrees);
    static int stepsToDegrees(long steps);
    static float degreesToSteps(int degrees);
    float m_roundAdj = 0;
    int direction = 1; // temporary variable for tmp function to turn around.
    mutable AccelStepper motor;
};