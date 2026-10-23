#include <string>
#include "Engine.hpp"


Engine::Engine(const EnginePins& pins) 
    : pins{pins},
      currentPower{0},
      targetPower{0} 
{

}

void Engine::begin()
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

void Engine::stop()
{
    if (currentPower == 0 && targetPower == 0) {
        return;
    }
    this->targetPower = 0;
    this->currentPower = 0;
    this->writeToMotorDriver();
}

void Engine::modifyPower()
{
    if (currentPower == targetPower) {
        return;
    }
    if (targetPower > currentPower) {
        const int rate = (currentPower >= 0) ? ACCELERATION_RATE : DECELERATION_RATE;
        currentPower = std::min(currentPower + rate, targetPower);
    }
    else {
        const int rate = (currentPower <= 0) ? ACCELERATION_RATE : DECELERATION_RATE;
        currentPower = std::max(currentPower - rate, targetPower);
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
    Serial.println();
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