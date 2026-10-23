#pragma once

#include <Arduino.h>
#include <Bluepad32.h>

class Joystick
{
public: // CONFIGURABLE CONSTANTS
    static constexpr float DEADZONE = 0.12;
public:
    void updatePos(int axisX, int axisY);
    float getX() const { return x; }
    float getY() const { return y; }

private:
    float x = 0;
    float y = 0;
};

class Button
{
public:
    void update(bool newState) {
        prevState = currentState;
        currentState = newState;
    }
    bool justPushed() const { return (not prevState and currentState); }
    bool justReleased() const { return (prevState and not currentState); }
    bool isDown() const { return (currentState); }
private:
    bool currentState = false;
    bool prevState = false;
};


class GamePadInput 
{
public:
    void processData(ControllerPtr ctl);
    void printData() const;
    const Joystick& getLeftJoystick() const { return left; }
    const Joystick& getRightJoystick() const { return right; }
    const Button& buttonX() const { return x; }
    const Button& buttonY() const { return y; }
    const Button& buttonB() const { return b; }
    const Button& buttonA() const { return a; }

private:
    Joystick left;
    Joystick right;

    Button x;
    Button y;
    Button b;
    Button a;


};
