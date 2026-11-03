#pragma once

class IntervalTimer
{
public:
    explicit IntervalTimer(unsigned long intervalMs) : interval{intervalMs}, lastCall{0} { }
    bool isReady() {
        const unsigned long now = millis();
        if (now - lastCall < interval) {
            return false;
        }
        lastCall += interval;
        if (now - lastCall >= interval) {
            lastCall = now;
        }
        return true;
    }
private:
    const unsigned long interval;
    unsigned long lastCall;
};