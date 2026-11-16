#pragma once

#include "ITurretMode.hpp"

class TurretManualMode : public ITurretMode
{
public: //CONFIGURABLE CONSTANTS
    static constexpr long RUN_DISTANCE = 1000L;
public:
    using ITurretMode::ITurretMode;
    void updateTurretTarget() override;
private:
    bool alreadyStopped = false;
};