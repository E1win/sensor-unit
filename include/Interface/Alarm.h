#pragma once

#include "Arduino.h"

class Alarm
{
public:
    Alarm(byte pin);

    void TurnOn();
    void TurnOff();

    bool IsOn() const;

private:
    static void Loop(void *params);

private:
    byte m_pin;

    bool m_alarmOn = false;

    int m_msDelay = 1000;
};