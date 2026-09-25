#pragma once

#include <Arduino.h>
#include <Bluepad32.h>

class Joystick
{
private:
    int x = 0;
    int y = 0;
    constexpr static int DEADZONE = 200;
public:
    void setPos(int axisX, int axisY);
    int getX() const { return x; }
    int getY() const { return y; }
};


class GamePadInput 
{
    Joystick left;
    Joystick right;

    bool x = false;
    bool y = false;
    bool b = false;
    bool a = false;

public:
    void updateData(ControllerPtr ctl);
    void printData() const;
};
