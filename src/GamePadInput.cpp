#include "GamePadInput.hpp"

void Joystick::updatePos(int axisX, int axisY)
{
    this->x = constrain(axisX / 512.0f, -1.0f, 1.0f);
    this->y = -1 * constrain(axisY / 512.0f, -1.0f, 1.0f);

    if (std::abs(x) < Joystick::DEADZONE) {
        x = 0;
    }
    if (std::abs(y) < Joystick::DEADZONE) {
        y = 0;
    }
}

void GamePadInput::processData(ControllerPtr ctl)
{
    left.updatePos(ctl->axisX(), ctl->axisY());
    right.updatePos(ctl->axisRX(), ctl->axisRY());

    x.update(ctl->x());
    y.update(ctl->y());
    b.update(ctl->b());
    a.update(ctl->a());
}

void GamePadInput::printData() const
{
    Serial.printf(
        "joystick L: (%2f, %2f), joystick R: (%2f, %2f), X: %d, Y: %d, B: %d, A: %d\n",
        left.getX(),
        left.getY(),
        right.getX(),
        right.getY(),
        x.isDown(),
        y.isDown(),
        b.isDown(),
        a.isDown()
    );
}