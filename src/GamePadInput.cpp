#include "GamePadInput.hpp"

void Joystick::setPos(int axisX, int axisY)
{
    this->x = axisX;
    this->y = axisY;

    if (std::abs(x) < Joystick::DEADZONE) {
        x = 0;
    }
    if (std::abs(y) < Joystick::DEADZONE) {
        y = 0;
    }
}

void GamePadInput::updateData(ControllerPtr ctl)
{
    left.setPos(ctl->axisX(), ctl->axisY());
    right.setPos(ctl->axisRX(), ctl->axisRY());

    x = ctl->x();
    y = ctl->y();
    b = ctl->b();
    a = ctl->a();
}

void GamePadInput::printData() const
{
    Serial.printf(
        "joystick L: (%4d, %4d), joystick R: (%4d, %4d), X: %d, Y: %d, B: %d, A: %d\n",
        left.getX(),
        left.getY(),
        right.getX(),
        right.getY(),
        x,
        y,
        b,
        a
    );
}