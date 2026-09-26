#include <string>
#include "Engine.hpp"

void Engine::drive(int power)
{
    if (power == 0) {
        this->targetState = State::NEUTRAL;
        this->targetPower = 0;
    }
    else if (power > 0) {
        this->targetState = State::FORWARD;
        this->targetPower = std::abs(power);
    }
    else {
        this->targetState = State::BACKWARD;
        this->targetPower = std::abs(power);
    }
    this->modifyPower();
    this->writeToMotorDriver();
}

void Engine::modifyPower()
{
    /*
        TODO apply acceleration step for engine power
        * Think of optimal Engine::ACCELERATION_RATIO value
        * This method should be the only place where currentPower is updated
    */
    if (currentPower < targetPower) {
        currentPower += ACCELERATION_RATE;
        if (currentPower > targetPower) {
            currentPower = targetPower;
        }
    } 
    else if (currentPower > targetPower) {
        currentPower -= ACCELERATION_RATE;
        if (currentPower < targetPower) {
            currentPower = targetPower;
        }
    }
}

void Engine::writeToMotorDriver() const
{
    /*
        TODO This method will be used to send real signals to motor driver
        * For now, the simulation should be implemented
    */
    Serial.printf(
        "C: %4d [%s], T: %4d [%s]   ", 
        currentPower, getCurrentStateName().c_str(),
        targetPower, getCurrentStateName().c_str()
    );
}


std::string Engine::getCurrentStateName() const
{
    switch(targetState)
    {
        case(State::FORWARD):
            return "F";
        case(State::BACKWARD):
            return "B";
        case(State::NEUTRAL):
            return "N";
        default:
            return "BRAKE";
    }
}