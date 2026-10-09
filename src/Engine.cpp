#include <string>
#include "Engine.hpp"


Engine::Engine(const EnginePins& pins) 
    : pins{pins},
      currentPower{0},
      targetPower{0} 
{

}

void Engine::begin() const
{
    pinMode(pins.in1, OUTPUT);
    pinMode(pins.in2, OUTPUT);
    pinMode(pins.pwm, OUTPUT);
    this->writeToMotorDriver();
}

void Engine::drive(int power)
{
    this->targetPower = power;
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
        currentPower = std::min(currentPower + ACCELERATION_RATE, targetPower);
    } 
    else if (currentPower > targetPower) {
        currentPower = std::max(currentPower - ACCELERATION_RATE, targetPower);
    }
}

void Engine::writeToMotorDriver() const
{
    digitalWrite(pins.in1, currentPower > 0);
    digitalWrite(pins.in2, currentPower < 0);
    analogWrite(pins.pwm, abs(currentPower));

    Serial.printf(
        "C: %4d [%s], T: %4d [%s]   ", 
        currentPower, getStateName(getCurrentState()).c_str(),
        targetPower, getStateName(getCurrentState()).c_str()
    );
}

Engine::State Engine::getCurrentState() const
{
    if (currentPower > 0) {
        return State::FORWARD;
    }
    if (currentPower < 0) {
        return State::BACKWARD;
    }
    return State::NEUTRAL;
}


std::string Engine::getStateName(State state) const
{
    switch(state)
    {
        case(State::FORWARD): return "F";
        case(State::BACKWARD): return "B";
        case(State::NEUTRAL): return "N";
        case(State::BRAKE): return "BRAKE";
        default: return "UNKNOWN";
    }
}