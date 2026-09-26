#pragma once

#include "Engine.hpp"

void Engine::drive(int power)
{
    if (power == 0) {
        this->currentState = State::NEUTRAL;
        this->targetPower = 0;
    }
    else if (power > 0) {
        this->currentState = State::FORWARD;
        this->targetPower = std::abs(power);
    }
    else {
        this->currentState = State::BACKWARD;
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
            currentPower = targetPower; // Zabezpieczenie przed przestrzeleniem
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
   Serial.printf("E: %4d  ", currentPower);
}