#pragma once

#include <Arduino.h>
#include <Bluepad32.h>

class Joystick
{
public:
    void updatePos(int axisX, int axisY);
    float getX() const { return x; }
    float getY() const { return y; }
    static constexpr float DEADZONE = 0.2;

private:
    float x = 0;
    float y = 0;
};


class GamePadInput 
{
public:
    void processData(ControllerPtr ctl);
    void printData() const;
    Joystick getLeftJoystick() const { return left; }
    Joystick getRightJoystick() const { return right; }
    bool isXpressed() { return x; }
    bool isYpressed() { return y; }
    bool isBpressed() { return b; }
    bool isApressed() { return a; }

private:
    Joystick left;
    Joystick right;

    bool x = false;
    bool y = false;
    bool b = false;
    bool a = false;


};
