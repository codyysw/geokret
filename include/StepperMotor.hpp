#include <AccelStepper.h>
#include "Config.hpp"
#include "IDriveMode.hpp"

class StepperMotor
{
public: // CONFIGURABLE CONSTANTS
    static constexpr int STEPS_PER_ROTATION = 2048;
    static constexpr int MAX_STEPS_PER_SECOND = 512;
    static constexpr int ACCELERATION = 500;
public:
    StepperMotor(StepperPins pins, AccelStepper::MotorInterfaceType type = AccelStepper::FULL4WIRE);
    void begin();
    bool run() { return motor.run(); }
    void move(long relative) { motor.move(relative); }
    void moveTo(long absolute) { motor.moveTo(absolute); }
    void stop() { motor.stop(); }
    long currentPosition() { return motor.currentPosition(); }
    long distanceToGo() { return motor.distanceToGo(); }
    void tmpMoveWithPad(const DriveContext& ctx);
private:
    AccelStepper motor;
};